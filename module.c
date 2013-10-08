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
  
  
	temp = strtok (input," ");
	
	while (temp != NULL) {
		command->argv[i] = temp;
		temp = strtok (NULL, " ");
		i++;
	}
	
    command->argc = i;
    command->argv[i++] = NULL; //a NULL spot lets us know we're at the end.
    
    return 0;
}




int Execvp(struct command_t *command)
{
	 pid_t pid;
	 pid = Fork();
	 execvp(command->name, command->argv);
	 
}

int Exec_file_in(struct command_t *command, int position)
{
	int pipefd[2];
	pid_t pid;
	pid = Fork();
	if (pipe(pipefd))
	{
		exit(1);
	}
	
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		FILE *input;
		char *temp;
		
		input = fopen(command->argv[position], "r");
		if (input == NULL)
		{
			return 1;
		}
		while ((temp = fgetc(input)) != EOF)
		{
			putchar(temp);
		}
		fclose(temp);
		return 0;
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	
	execvp(command->name, command->argv);
	return 0;
}



int Exec_file_out(struct command_t *command, int position)
{
	pid_t pid;
	int temp = dup(1);
	char *file_name = command->argv[position];
	int file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if(file < 0)    return 1;
    
    if (dup2(file, 1) < 0) 
    {
    	return 1;
    }
	pid = Fork();
	if (pid == 0) 
	{
		close(file);
		close(temp);
		execvp(command->name, command->argv);
		return 0;
	}
	dup2(temp, 1);
	close(file);
	close(temp);
	wait(NULL);
	return 0;
}


int Exec_pipe(struct command_t *command, int position)
{
	return 0;
}

int Exec(struct command_t *command)
{
	return 0;
}

int Process(struct command_t *command)
{
	int i = 0;
	int new_in = 0;
	int new_out = 0;
	int pipes = 0;
	
	char *new_in_file;
	char *new_out_file;
	
	for (i; i<command->argc; i++)
	{
		if (strcmp(command->argv[i], ">") == 0)
		{
    		Exec_file_out(command, i);
    	}
    	
    	if (strcmp(command->argv[i], "<") == 0)
		{
    		fflush(stdout);
    		pid_t pid;
    		pid = Fork();
    		if (pid == 0)
    		{
    			Exec_file_in(command, i);
    		}
    		wait(pid);
    	}
    	
    	if (strcmp(command->argv[i], "|") == 0)
    	{
    		Exec_pipe(command, i);
    	}
    	else
    	{
    	Exec(command);
    	}
    }
    return 0;
}

int Path(char *path)
{
	int i = 0;
	char *temp;
	char *temp_path = getenv("PATH");
	temp = strtok(temp_path, ":");
	while(temp != NULL) {
		temp = strtok(NULL, ":");
		path[i] = *temp;
		i++;
	}
	path[i++] = NULL;
	 
	 return 0;
}
	 
	 
	 
	 
	 
	 
    	
    	