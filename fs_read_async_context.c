#include <stdlib.h>
#include <stdio.h>
#include <uv.h>

#define BUF_SIZE 100
static const char *filename = "dummy.txt";

void check(int r) {
    if(r < 0) {
        printf("Error");
        exit(1);
    }
}


typedef struct context_struct {
    uv_fs_t *open_req;
    uv_buf_t iov;
} context_t;

void read_cb(uv_fs_t* read_req) {
    int r = 0;
    check(read_req->result);

    /* extracting our context from the read_req */
    context_t* context = read_req->data;

    /*Report the contents of the buffer */
    printf("The text is -> %s", context->iov.base);

    free(context->iov.base);

    /* 5. Close the file descriptor (synchronously) */
    uv_fs_t close_req;
    r = uv_fs_close(uv_default_loop(), &close_req, context->open_req->result, NULL);
    check(r);

    /* cleanup all requests and context */
    uv_fs_req_cleanup(context->open_req);
    uv_fs_req_cleanup(read_req);
    uv_fs_req_cleanup(&close_req);
    free(context);
}

void init(uv_loop_t *loop) {
    int r = 0;

    /* No more globals, we need to malloc each request and pass it around for later cleanup */
    uv_fs_t *open_req = malloc(sizeof(uv_fs_t));
    uv_fs_t *read_req = malloc(sizeof(uv_fs_t));

    // context will point open req and buffer
    context_t *context = malloc(sizeof(context_t));
    context->open_req  = open_req;

    // Opens the file synchronously
    // O_RDONLY is File Status Flag ie open for reading only 
    // S_IRUSR is system flag - R for owner 
    r = uv_fs_open(loop, open_req, filename, O_RDONLY, S_IRUSR, NULL);
    check(r);

    // Create buffer and initialize it to turn it into a a uv_buf_t *
    char *buf = malloc(sizeof(char) * (BUF_SIZE));
    uv_buf_t iov = uv_buf_init(buf, BUF_SIZE);
    context->iov = iov;

    /* allow us to access the context inside read_cb */
    // read_req->data is actually a void *pointer so it is able to point to our struct context_t
    read_req->data = context;

    /* Use the file descriptor (the .result of the open_req) to read **aynchronously** from the file into the buffer */
    // we have 1 buffer to give, -1 is the starting offset
    r = uv_fs_read(loop, read_req, open_req->result, &iov, 1,  -1, read_cb);
    check(r);
}

int main() {
    uv_loop_t *loop = uv_default_loop();

    init(loop);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);

    return 0;
}
