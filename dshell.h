#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define PROMPT "\ndan_shell> "

#define MAX_INPUT 256

void unix_error(char *msg);
pid_t Fork(void);


typedef struct commands {
    char command_name[128]; //random guess. adjust as needed
    char params[256];       //another random guess
    char new_std_in[128];
    char new_std_out[128];
} commands;
