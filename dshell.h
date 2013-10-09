//////////////////////////////////////////////////////////
//Dan McGinnis
//mcginnis.dan@gmail.com
//CIS 3207 Fall 2013
//Lab 2 October 9, 2013
//"Bash" style shell
//
////////////////////////////////////////////////////////////





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PROMPT "dan_shell> "
#define MAX_INPUT 4096

char input[MAX_INPUT];

typedef struct command {
    char *name;
    int argc;
    char *argv[MAX_INPUT];
    
} Command;



void unix_error(char *msg);
pid_t Fork(void);
void Clear_screen(void);
int Parse(char *input, Command *command);
int Process(Command *command);
int Exec_file_out(Command *command, int position);
int Exec_file_in(Command *command, int position);
int Exec_pipe(Command *command, int position);
int Exec(Command *command);
int Exec_bg(Command *command);



