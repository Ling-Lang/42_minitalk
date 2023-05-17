CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_SRV = src/server.c
SRC_CLI = src/client.c

OBJ_SRV = $(SRC_SRV:.c=.o)
OBJ_CLI = $(SRC_CLI:.c=.o)

LIBINC = -I./libft
LIB = libft/libft.a

all: client server lft

client: $(OBJ_CLI) | lft
	$(CC) $(CFLAGS) -o $@ $(OBJ_CLI) $(LIB)

server: $(OBJ_SRV) | lft
	$(CC) $(CFLAGS)  -o $@ $(OBJ_SRV) $(LIB)

lft:
	(cd libft && make all && make clean)

clean:
	rm -f $(OBJ_SRV) $(OBJ_CLI)

fclean: clean
	rm -f client server

make re: fclean all
