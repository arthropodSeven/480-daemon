#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 5858

int main()
{
    // setup the client socket stream using IPv4
    int client_socket = socket ( AF_INET, SOCK_STREAM, 0 );

    // this sockaddr_in struct will hold all the information needed to connect
    // with the server
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    server_address.sin_port = htons( PORT );


    // connect to the server address using the cliend socket. If connect is
    // not zero, the connecting failed.
    if( connect( client_socket, (struct sockaddr *)&server_address, 
                sizeof(server_address)) != 0 )
    {
        printf ( "Error connecting to server\n" );
        exit(EXIT_FAILURE);
    }

    // loop for user input
    while(1)
    {
        printf ("Enter character: \n" );
        char input, output;

        // read a char from stdin
        read( 0, &input, sizeof(char) );
        // write the char to the socket
        write( client_socket, &input, sizeof(char) );
        // read server response from the socket
        read( client_socket, &output, sizeof(char) );

        printf( "%c\n", output );
        break;
    }
    exit(EXIT_SUCCESS);
}
