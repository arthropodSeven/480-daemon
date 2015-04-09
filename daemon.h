#include<stdio.h>
#include<syslog.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/types.h>

int daemon_init ();
int daemon_kill ();
