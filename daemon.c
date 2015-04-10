#include "daemon.h"

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
        printf( "with a kiss, I die\n" );
        exit( EXIT_SUCCESS );
    }
    else
    {
        printf( "Aha! I'm in the background." );
        printf( "First, open the syslog\n" );
        // Open the log: indicate our name, write directly to console if
        // can't write to log; indicate that we're a daemon
        openlog( "daemon_480", LOG_CONS | LOG_PID , LOG_DAEMON );
    }
}

void daemon_kill( int signal )
{
    syslog( LOG_INFO, "Daemon closing" );
    closelog();
    printf( "Log closed. Exiting.\n" );
    exit( EXIT_SUCCESS );
}
