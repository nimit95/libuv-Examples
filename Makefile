hello_world: hello_world.c
	gcc -o main hello_world.c /usr/local/lib/libuv.a -pthread
clean:
	rm main