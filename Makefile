CC=gcc
CFLAGS=-Wall -Wextra -c

run: captcha
	./captcha

build: captcha
	$(CC) captcha.o -o captcha

captcha.o: captcha.c bmp_header.h
	$(CC) $(CFLAGS) $^

clean:
	rm -rf captcha.o captcha *_task*
