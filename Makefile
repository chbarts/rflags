CFLAGS = -O3 -march=native

all: rflags

rflags: rflags.c
	gcc $(CFLAGS) rflags.c -o rflags

clean:
	rm rflags
