#include"daemon.h"

int main( int argc, char* argv )
{
    i = 0;
    while( true )
    {
        sleep(5);
        syslog( LOG_INFO, "This is message number %d after %d seconds", i,
                (5*i) );
        i++;
    }
}
