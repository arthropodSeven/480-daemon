#include "daemon.h"
#define PORT 5858
#define NUM_CXNS 10

void daemon_init ()
{
    pid_t my_pid;

    my_pid = fork();
    if( my_pid < 0 )
    {
        printf( "Something broke. Exit.\n" );
        exit( EXIT_FAILURE );
    }
    else if( my_pid > 0 )
    {
        printf( "Pid greater than zero. See ya.\n" );
        exit( EXIT_SUCCESS );
    }
    else
    {
        printf( "Aha! I'm in the background.\n" );
        printf( "First, open up a socket.\n" );

        // Domain - AF_INET, type - SOCK_STREAM, protocol - 0 (default)
        int server_socket = socket( AF_INET, SOCK_STREAM, 0);
        // Struct holding information about our incoming address
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
        server_address.sin_port = htons( PORT );

        // Bind the socket to our address
        bind( server_socket, (struct sockaddr *)&server_address,
                sizeof(server_address));

        // Listen for macro-defined number of connections
        if( (listen( server_socket, NUM_CXNS )) != 0)
        {
            printf( "Server at PID %d: error listening for connection.\n",
                    my_pid );
            printf( "Errno: %d", errno );
            exit( EXIT_FAILURE );
        }

        // Spawn threads when connection received
        while( true )
        {
            // NULLs refer to a sockaddr struct to fill, and the size of
            // that struct, respectively. They're not needed here because we
            // aren't filling an existing struct. client_socket will be a
            // file descriptor pointing to the open socket.
            int client_socket = accept( server_socket, NULL, NULL );

            // Make a thread to handle the request
            pthread_t new_thread;
            
            // The NULL here refers to thread attributes--this thread
            // doesn't need any special ones.
            if( (pthread_create (&new_thread, NULL, client_handler,
                        (void *)&client_socket)) != 0 )
            {
                printf( "Server at pid %d: some error spawning a thread.\n",
                        my_pid );
                exit( EXIT_FAILURE );
            }

            if( (pthread_detach (new_thread) ) != 0 )
            {
                printf( "Server at pid %d: a thread failed to detach.\n",
                        my_pid );
                exit( EXIT_FAILURE );
            }

        }
    }
}

void * client_handler ( void *v_args )
{   // Method for spawned threads to use in handling client requests.

    // Turn the void pointer into a pointer to int
    int *args = (int *)v_args;
    // Fetch the int value from the pointer to int, and put it into
    // client_socket
    int client_socket = *args;
    
    // Take one character of input at a time
    char input;
    bool found_q = false;
    
    // We read one character and check for end of file (if we get
    // EOF or EOT signal, read() will return 0)
    while( !found_q )
    {
        read( client_socket, &input, sizeof(char) );
        // Write that back, if it wasn't EOF/EOT or 'q'
        if( input != 'q' )
            write( client_socket, &input, sizeof(char) );
        else
            found_q = true;;
    }

    // We caught EOF/EOT, so clean up
    close( client_socket );
    pthread_exit( NULL );

}
