CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
NAME=fastest_sort

objs:
		$(CC) $(CFLAGS) -c fastest_sort.c

all: objs
		${CC} ${CFLAGS} fastest_sort.o -o $(NAME)

clean:
		rm -f fastest_sort.o

fclean: clean
		rm -f $(NAME)

re: fclean all
