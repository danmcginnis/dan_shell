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
    char pipes[MAX_PIPES];
    
    int i = 0;
    char *temp;
    char *remains;
    
    int j = 0;
    
    
    
    
	temp = strtok (input," ");
	
	while (temp != NULL) {
		command->argv[i] = temp;
		temp = strtok (NULL, " ");
		i++;
	}
	strncpy(command->name, command->argv[0], strlen(command->argv[0]));
	strncat(command->name, "\0", 1); // cmd holds the name of the command name now
    
    /*command->name = strtok_r(input, " ", &remains);
    strncat(command->name, "\0", 1); // string concatenation; a string ends with '\0'
    
    temp = strtok(remains, " ");
    while (temp != NULL)
    {
        command->argv[i] = temp;
        temp = strtok(NULL, " ");
        i++;
    } */
	
	
    command->argc = i;
    command->argv[i++] = NULL; //a NULL spot lets us know we're at the end.
    
    return 0;
}


int Process(struct command_t *command)
{
	int i = 0;
	for (i; i<command->argc; i++)
	{
		if (strcmp(command->argv[i], ">") == 0)
		{
    		printf("redirect found for %s\n", command->argv[i+1]);
    	}
    	
    	if (strcmp(command->argv[i], "<") == 0)
		{
    		printf("redirect found\n");
    	}
    }
    return 0;
}

int Execvp(struct command_t *command)
{
	 pid_t pid;
	 pid = Fork();
	 execvp(command->name, command->argv);
	 
}
	 
	 
	 
	 
	 
	 
	 
    	
    	