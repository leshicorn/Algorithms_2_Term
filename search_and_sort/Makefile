NAME=f_number
C=	 f_number.c
OBJ= f_number.o
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
	rm out.txt
	
	