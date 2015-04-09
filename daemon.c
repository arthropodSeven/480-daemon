#include<stdio.h>
#include<syslog.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>

int main( int argc, char* argv )
{
    pid_t my_pid;
    int file_desc;
    int i;

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
        printf( "Aha! I'm in the background.\n" );
        printf( "First, open the syslog\n" );
        // Open the log: indicate our name, write directly to console if
        // can't write to log; indicate that we're a daemon
        openlog( "daemon_480", LOG_CONS | LOG_PID , LOG_DAEMON );

    }
}
