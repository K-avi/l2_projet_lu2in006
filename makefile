CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter -std=c11
#CFLAGS = -g -Wno-unused-parameter
CC = gcc
ALLPROGS= test prog

.PHONY:	all clean

all: $(ALLPROGS) 

test: listeChaine.o ex3.o main_test.o
	$(CC) -o $@ $(CFLAGS) $^

prog: listeChaine.o main_prog.o
	$(CC) -o $@ $(CFLAGS) $^


%.o:%.c %.h
	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(ALLPROGS)
