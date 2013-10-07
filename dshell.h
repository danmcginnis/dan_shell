#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

#define PROMPT "dan_shell> "

#define MAX_INPUT 4096

char input[MAX_INPUT];

struct command_t {
    char *name;
    int argc;
    char *argv[MAX_INPUT];
    char *new_std_in;
    char *new_std_out;
};



void unix_error(char *msg);
pid_t Fork(void);
void Clear_screen(void);
int Parse(char *input, struct command_t *command);



