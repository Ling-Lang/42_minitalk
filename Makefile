CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_SRV = server.c
SRC_CLI = client.c

OBJ_SRV = $(SRC_SRV:.c=.o)
OBJ_CLI = $(SRC_CLI:.c=.o)

LIBINC = -I./libft
LIB = libft/libft.a

all: client server lft

client: $(OBJ_CLI) | lft
	$(CC) $(CFLAGS) $(LIB) -o $@ $(OBJ_CLI)

server: $(OBJ_SRV) | lft
	$(CC) $(CFLAGS) $(LIB) -o $@ $(OBJ_SRV)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

lft:
	(cd libft && make all && make clean)

clean:
	rm -f $(OBJ_SRV) $(OBJ_CLI)

fclean: clean
	rm -f client server

make re: fclean all
