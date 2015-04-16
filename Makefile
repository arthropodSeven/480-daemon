all: main 

main: main.o daemon.o
	gcc -pthread -Wall main.o -o main daemon.o

main.o: main.c
	gcc -pthread -Wall -c main.c

daemon.o: daemon.c
	gcc -pthread -Wall -c daemon.c

clean:
	rm -rf *o main

