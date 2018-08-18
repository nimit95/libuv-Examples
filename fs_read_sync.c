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

int main() {
    
    uv_loop_t* loop = uv_default_loop();

    uv_fs_t* open_req = malloc(sizeof(uv_fs_t));
    // O_RDONLY is File Status Flag ie open for reading only 
    // S_IRUSR is system flag - R for owner 
    int r = uv_fs_open(loop, open_req, filename, O_RDONLY, S_IRUSR, NULL);

    check(r);

    uv_fs_t* read_req = malloc(sizeof(uv_fs_t));
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(buf));
    uv_buf_t iov = uv_buf_init(buf, BUF_SIZE);

    r = uv_fs_read(loop, read_req, open_req->result, &iov, 1, -1, NULL);
    check(r);

    printf("The text is ->  %s", buf);

    uv_fs_t* close_req = malloc(sizeof(uv_fs_t));
    r = uv_fs_close(loop, close_req, open_req->result, NULL);
    check(r);

    uv_fs_req_cleanup(open_req);
    uv_fs_req_cleanup(read_req);
    uv_fs_req_cleanup(close_req);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    return 0;


}

