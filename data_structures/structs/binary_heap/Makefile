NAME=bh
C=	 bh.c
OBJ= bh.o
CC=gcc
CFLAGS=-Wall -Wextra

objs:
	$(CC) -c $(C) ${CFLAGS}

all: objs
	$(CC) $(OBJ) ${CFLAGS} -o $(NAME)

clean:
	rm $(OBJ) $(NAME)

re: clean all

all_objs_delete:
	find . -type f -name '*.o' -exec rm {} +

executables_delete:
	find . -type f -executable -exec rm {} +

delete: all_objs_delete executables_delete
