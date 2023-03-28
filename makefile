CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter 

CC = gcc
ALLPROGS= test myGit



SRC:=ex1.o listeChaine.o ex3.o ex4.o ex5.o ex6.o ex7.o ex8.o ex9.o

all: $(ALLPROGS) 

test: $(SRC) main_test.o
	$(CC) -o $@ $(CFLAGS) $^

myGit: $(SRC) myGit.o
	$(CC) -o $@ $(CFLAGS) $^


%.o:%.c %.h
	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(ALLPROGS)

.PHONY:	clean
