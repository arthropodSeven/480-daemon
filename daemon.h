#include<stdio.h>
#include<syslog.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>

int daemon_init ();
void daemon_kill( int signal );
