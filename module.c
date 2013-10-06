#include "dshell.h"



//Page 718 of computer systems
void unix_error(char *msg) 
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}


pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        unix_error("Fork error");
    return pid;
}
