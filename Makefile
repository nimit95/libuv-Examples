all: hello_world idle_basic
hello_world: hello_world.c
	gcc -o hello_world hello_world.c /usr/local/lib/libuv.a -pthread
idle_basic: idle_basic.c
	gcc -o idle_basic idle_basic.c /usr/local/lib/libuv.a -pthread
fs_read_sync: fs_read_sync.c
	gcc -o fs_read_sync fs_read_sync.c /usr/local/lib/libuv.a -pthread	
fs_read_async: fs_read_async.c
	gcc -o fs_read_async fs_read_async.c /usr/local/lib/libuv.a -pthread	
clean:
	rm hello_world idle_basic fs_read_sync 2> /dev/null