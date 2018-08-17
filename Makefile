all: hello_world idle_basic
hello_world: hello_world.c
	gcc -o hello_world hello_world.c /usr/local/lib/libuv.a -pthread
idle_basic: idle_basic.c
	gcc -o idle_basic idle_basic.c /usr/local/lib/libuv.a -pthread
clean:
	rm main, idle_basic