#include<errno.h>
#include<stdio.h>
#include<syslog.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


// Globals
int* g_memo_array[ 256 ];

void daemon_init ();
void daemon_kill( int signal );
void *client_handler( void *v_args );

int riemann( int input );
int memo_find( int input );
int memo_add( int input, int iterations );
