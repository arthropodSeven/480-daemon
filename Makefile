all: main 

main: main.o daemon.o
	gcc -Wall main.o -o main daemon.o

main.o: main.c
	gcc -Wall -c main.c

daemon.o: daemon.c
	gcc -Wall -c daemon.c

clean:
	rm -rf *o main

