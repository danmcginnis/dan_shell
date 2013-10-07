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
    {
        unix_error("Fork error");
        return pid;
    }
}

void Clear_screen(void)
{
    printf("\033[2J\033[1;1H");
}


int Parse(char *input, struct command_t *command)
{
    int i = 0;
    char *temp;
    char *remains;
    
    command->name = strtok_r(input, " ", &remains);
    
    temp = strtok(remains, " ");
    while (temp != NULL)
    {
        command->argv[i] = temp;
        printf("Next arg = %s\n", temp);
        temp = strtok(NULL, " ");
        i++;
    }

    command->argc = i;
    command->argv[i++] = NULL; //what is this doing?
	
    return 0;
}
    