CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: client server

client: client.c
	$(CC) $(CFLAGS) -o $@ $^

server: server.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f client server
