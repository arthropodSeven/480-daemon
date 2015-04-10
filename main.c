#include"daemon.h"

int main( int argc, char* argv )
{
    daemon_init();
    signal( SIGTERM, daemon_kill );

    int i = 0;
    while( true )
    {
        syslog( LOG_INFO, "This is message number %d after %d seconds", i,
                (5*i) );
        i++;
        sleep(5);
    }
}
