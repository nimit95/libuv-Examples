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

/* Making our lifes a bit easier by using this global, a better solution in the next example ;) */
static uv_fs_t open_req;
static uv_buf_t iov;

void read_cb(uv_fs_t* read_req) {
    int r = 0;
    check(read_req->result);

    printf("The text is -> %s", iov.base);

    /* Close the file descriptor */
    uv_fs_t close_req;
    uv_fs_close(uv_default_loop(), &close_req, open_req.result, NULL);
    check(r);

    uv_fs_req_cleanup(&open_req);
    uv_fs_req_cleanup(read_req);
    uv_fs_req_cleanup(&close_req);
}

    int main() {
    int r = 0;
    uv_loop_t *loop = uv_default_loop();

    // Opens the file synchronously
    // O_RDONLY is File Status Flag ie open for reading only 
    // S_IRUSR is system flag - R for owner 
    r = uv_fs_open(loop, &open_req, filename, O_RDONLY, S_IRUSR, NULL);
    check(r);

    // buffer and initialize it to turn it into a a uv_buf_t *
    char buf[BUF_SIZE + 1];
    memset(buf, 0, sizeof(buf));
    iov = uv_buf_init(buf, BUF_SIZE);

    /* Use the file descriptor (the .result of the open_req) to read **aynchronously** from the file into the buffer */
    // we have 1 buffer to give, -1 is the starting offset
    uv_fs_t read_req;
    r = uv_fs_read(loop, &read_req, open_req.result, &iov, 1, -1, read_cb);
    check(r);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    return 0;
}
