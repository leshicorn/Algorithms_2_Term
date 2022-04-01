CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
NAME=binary_heap

objs:
		$(CC) $(CFLAGS) -c binary_heap.c

all: objs
		${CC} ${CFLAGS} binary_heap.o -o $(NAME)

clean:
		rm -f binary_heap.o

fclean: clean
		rm -f $(NAME)

re: fclean all
