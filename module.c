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


int Parse(char *input, Command *command)
{
    
   
    int i = 0;
    char *temp;
    
    
	temp = strtok(input," \n");
	command->name = temp;
	strncat(command->name, "\0", 1);
	
	while (temp != NULL) {
		command->argv[i] = temp;
		temp = strtok(NULL, " \n");
		i++;
	}
	
    command->argc = i;
    command->argv[i] = NULL; //a NULL spot after the last argument lets us know we're at the end.
    
    return 0;
}



int Exec_file_in(Command *command, int position)
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
		FILE *fp;
		char *temp;
		
		fp = fopen(command->argv[position+1], "r");
		if (fp == NULL)
		{
			return 1;
		}
		while ((temp = fgetc(input)) != EOF)
		{
			putchar(temp);
		}
		fclose(fp);
		return 0;
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	command->argv[position] = NULL;
	execvp(command->name, command->argv);
	return 0;
}



int Exec_file_out(Command *command, int position)
{
	FILE *fp;
	pid_t pid;
	int temp = dup(1);
	char *file_name = command->argv[position+1];
	command->argv[position] = NULL;
	fp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if(fp == NULL)    
    {
    	return 1;
    }
	pid = Fork();
	if (pid == 0) 
	{
		close(fp);
		close(temp);
		execvp(command->name, command->argv);
		wait(NULL);
		return 0;
	}
	dup2(temp, 1);
	fclose(fp);
	close(temp);
	wait(NULL);
	return 0;
}


int Exec_pipe(Command *command, int position)
{
	
	char *name_1;
	char *name_2;
	char *argv1[1024];
	char *argv2[1024];
	int i = 0;
	int j = position;
	int k = 0;
	int pfd[2];
	
	for (i; i < position; i++)
	{
		argv1[i] = command->argv[i];
	}
	name_1 = strdup(command->argv[1]);
	argv1[position] = NULL;
	
	for (j; j < command->argc; j++)
	{
		argv2[k] = command->argv[j];
		k++;
	}
	name_2 = strdup(command->argv[position]);
	argv2[command->argc] = NULL;
	
	if(pipe(pfd) < 0) 
	{
		perror("Error on creating pipes!\n");
		exit(EXIT_FAILURE);
    }
    
    pid_t pid;
	pid = Fork(); // first command
	if (pid == 0)
	{
		if (pid == 0)
		{
			wait(NULL);
		}
		else
		{
			close(0); 
        	dup(pfd[0]);
        	close(pfd[1]);
        	execvp(name_2, argv2);
        }
    }
    else
    {
    	close(1); 
        dup(pfd[1]);
 	    close(pfd[0]);
        execvp(name_2, argv2);
    }
    
	
	
	
	return 0;
}

int Exec(Command *command)
{
	pid_t pid;
	pid = Fork();
	if (pid == 0)
	{
		execvp(command->name, command->argv);
	}
	else
	{
		wait(NULL);
	}
	
	return 0;
}

int Process(Command *command)
{
	int i = 0;
	
	
	for (i; i<command->argc; i++)
	{
		if (strcmp(command->argv[i], ">") == 0)
		{
    		Exec_file_out(command, i);
    		break;
    	}
    	
    	if (strcmp(command->argv[i], "<") == 0)
		{
    		printf("Argv[i+1] %s\n", command->argv[i+1]);
    		fflush(stdout);
    		pid_t pid;
    		pid = Fork();
    		if (pid == 0)
    		{
    			Exec_file_in(command, i);
    		}
    		wait(&pid);
    		break;
    	}
    	
    	if (strcmp(command->argv[i], "|") == 0)
    	{
    		Exec_pipe(command, i);
    		break;
    	}
    }
    	
    	
    	Exec(command);
    	
    
    return 0;
}
   	
    	