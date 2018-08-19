#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    // Will quit as nothing to process in this event loop
    
    printf("Now quitting\n");
    
    uv_loop_close(loop);
    free(loop);
    return 0;
}
