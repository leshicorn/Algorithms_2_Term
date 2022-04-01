CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
NAME=stack

objs:
		$(CC) $(CFLAGS) -c stack.c

all: objs
		${CC} ${CFLAGS} stack.o -o $(NAME)

clean:
		rm -f stack.o

fclean: clean
		rm -f $(NAME)

re: fclean all
