#include <stdio.h>
#include <uv.h>

int64_t counter = 0;
void wait_for_a_while(uv_idle_t* handle) {
    counter++;

    if(counter >= 10e6) {
        printf("Idling complete...\n");
        uv_idle_stop(handle);
    }
}

int main() {
    uv_idle_t* idler;

    /*  initialize an idle handler for the loop */
    uv_idle_init(uv_default_loop(), idler);
    uv_idle_start(idler, wait_for_a_while);

    printf("Idling...\n");

    /*  start the event loop */
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);


    uv_loop_close(uv_default_loop());
    free(idler);
    return 0;
}