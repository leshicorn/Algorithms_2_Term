CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
NAME=vector

objs:
		$(CC) $(CFLAGS) -c vector.c

all: objs
		${CC} ${CFLAGS} vector.o -o $(NAME)

clean:
		rm -f vector.o

fclean: clean
		rm -f $(NAME)

re: fclean all
