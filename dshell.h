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
#define MAX_PIPES 4

char input[MAX_INPUT];
char path[64];

struct command_t {
    char *name;
    int argc;
    char *argv[MAX_INPUT];
    
};



void unix_error(char *msg);
pid_t Fork(void);
void Clear_screen(void);
int Parse(char *input, struct command_t *command);
int Process(struct command_t *command);
int Execvp(struct command_t *command);
int Path(char *path);
int Exec_file_out(struct command_t *command, int position);
int Exec_file_in(struct command_t *command, int position);
int Exec_pipe(struct command_t *command, int position);
int Exec(struct command_t *command);



