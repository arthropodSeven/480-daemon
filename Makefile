all: main client

main: main.o daemon.o
	gcc -pthread -Wall main.o -o main daemon.o

main.o: main.c
	gcc -pthread -Wall -c main.c

daemon.o: daemon.c
	gcc -pthread -Wall -c daemon.c

client: client.o
	gcc -Wall -o client client.o

client.o: client.c
	gcc -Wall -c client.c

clean:
	rm -rf *o main client

