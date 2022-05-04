CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -g
NAME=	 hash_t
CNAME=	 hash_t.c
OBJ_NAME=hash_t.o

objs:
		$(CC) $(CFLAGS) -c $(CNAME)

all: objs
		${CC} ${CFLAGS} $(OBJ_NAME) -o $(NAME)

clean:
		rm -f $(OBJ_NAME)

fclean: clean
		rm -f $(NAME)

re: fclean all

all_objs_delete:
	find . -type f -name '*.o' -exec rm {} +

executables_delete:
	find . -type f -executable -exec rm {} +

delete: all_objs_delete executables_delete