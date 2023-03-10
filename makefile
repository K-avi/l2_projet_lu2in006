CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter 
#CFLAGS = -g -Wno-unused-parameter
CC = gcc
ALLPROGS= test prog

.PHONY:	all clean

all: $(ALLPROGS) 

test: ex1.o listeChaine.o ex3.o ex4.o ex5.o main_test.o
	$(CC) -o $@ $(CFLAGS) $^

prog: listeChaine.o ex1.o main_prog.o
	$(CC) -o $@ $(CFLAGS) $^


%.o:%.c %.h
	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(ALLPROGS)
