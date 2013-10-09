//////////////////////////////////////////////////////////
//Dan McGinnis
//mcginnis.dan@gmail.com
//CIS 3207 Fall 2013
//Lab 2 October 9, 2013
//"Bash" style shell
//
////////////////////////////////////////////////////////////





#include "dshell.h"


//Copied from page 718 of "Computer Systems: A Programmer's Perspective" by
//	Bryant & O'Hallaron
//	
//	This function wraps error handling to reduce code clutter.
//
//
void unix_error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}


//Copied from page 718 of "Computer Systems: A Programmer's Perspective" by
//	Bryant & O'Hallaron
//	
//	This function wraps error handling to reduce code clutter.
//
//
pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) 
    {
        unix_error("Fork error");
        return pid;
    }
}


//I found this hex code referenced under several sites while searching for a simple
//	way to clear the screen.
//
//
void Clear_screen(void)
{
    printf("\033[2J\033[1;1H");
}



//Parse(char *input, Command *command)
//
//Input:
//	An input string of characters
//	A struct of type Command
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	This function changes the struct passed to it.
//
//Assumptions:
//	Valid characters in input.
//	Struct has already been allocated.
//
//This function tokenizes the input string based on spaces
//	and places the first word found into the "name" field
//	of the struct. The entire string is placed in the "argv"
//	field and is terminated with a NULL character.
//
//
int Parse(char *input, Command *command)
{
    
    int i = 0;
    char *temp;
    
	temp = strtok(input," \n"); 
	command->name = temp;
	strncat(command->name, "\0", 1); //the first word won't have this ending if there is arguments.
	
	while (temp != NULL) {
		command->argv[i] = temp;
		temp = strtok(NULL, " \n");
		i++;
	}
	
    command->argc = i;
    command->argv[i] = NULL; //a NULL spot after the last argument lets us know we're at the end.
    
    return 0;
}



//Exec_file_in(Command *command, int position)
//
//Input:
//	A struct of type Command
//	An integer indicating the position of the file name in the argv field.
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	Nonthing
//
//Assumptions:
//	A positive integer in input.
//	Struct has already been allocated.
//
//This function attempts to open the file listed and pass its content into 
//	the command instead of accepting from the standard input.
//
//	See detailed explanation of execvp in Exec() function.
//
// !!!!!Currently not functional!!!!!
//
//
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
		while ((temp = fgetc(fp)) != EOF)
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




//Exec_file_out(Command *command, int position)
//
//Input:
//	A struct of type Command
//	An integer indicating the position of the file name in the argv field.
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	Nothing
//
//Assumptions:
//	A positive integer in input.
//	Struct has already been allocated.
//
//This function attempts to open the file listed and write the output to it instead
//	of the standard out.
//
// 
//	See detailed explanation of execvp in Exec() function.
//
//
int Exec_file_out(Command *command, int position)
{
<<<<<<< HEAD
	int fp;
=======
	FILE *fp;
>>>>>>> fac14b6ba92427d03cb25cfd61a9425c2a0d0f8d
	pid_t pid;
	char *file_name = command->argv[position+1];
<<<<<<< HEAD
    printf("file name %s\n", file_name);
	command->argv[position] = NULL;
    //the following command was one of the recommended command strings
    //  to safely open files according to several google searches
	fp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if(fp < 0)    
=======
	command->argv[position] = NULL;
	fp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if(fp == NULL)    
    {
    	return 1;
    }
    if (dup2(fp, 1) < 0) 
>>>>>>> fac14b6ba92427d03cb25cfd61a9425c2a0d0f8d
    {
    	return 1;
    }
	pid = Fork();
	if (pid == 0) 
	{
		close(fp);
		execvp(command->name, command->argv);
		wait(NULL);
		return 0;
	}
	dup2(fp, 1);
	wait(NULL);
	return 0;
}



//Exec_pipe(Command *command, int position)
//
//Input:
//	A struct of type Command
//	An integer indicating the position of the pipe in the argv field.
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	Nothing
//
//Assumptions:
//	A positive integer in input.
//	Struct has already been allocated.
//
//This function attempts to open a pipe and use it to pass the output of program 1
//	into the input of program 2.
//	See detailed explanation of execvp in Exec() function.
//
// !!!!!Currently not functional!!!!!
//
//
int Exec_pipe(Command *command, int position)
{
	
<<<<<<< HEAD
	char *name_2;
	char *argv2[1024];
	int i = 0;
	int j = position+1;
	int pipefd[2];
	pid_t pid_1;
    pid_t pid_2;
	
	command->argv[position] = NULL;
	
    //Quick and dirty way to generate second programs info.
    // This hack should be replaced with a call to parse to 
    // populate a second struct.
	for (j; j < command->argc+1; j++)
	{
		argv2[i] = command->argv[j];
		i++;
	}
	name_2 = strdup(command->argv[position+1]);
	argv2[command->argc] = NULL;
	
	if(pipe(pipefd) < 0) 
	{
		exit(1);
    }
    
	pid_1 = Fork(); // open fork for second command
	if (pid_1 == 0)
	{
		pid_2 = Fork(); // open fork for first command
		if (pid_2 == 0)
		{
			wait(NULL);
		}
		else
		{
			close(pipefd[1]); 
        	dup2(pipefd[0], STDIN_FILENO);
        	execvp(command->name, command->argv);
        }
    
    	close(pipefd[0]); 
        dup2(pipefd[1], 1);
        execvp(name_2, argv2);
    }
=======
	char *name_1;
	char *name_2;
	char *argv1[1024];
	char *argv2[1024];
	int i = 0;
	int j = position;
	int k = 0;
	
	for (i; i < position; i++)
	{
		argv1[i] = command.argv[i];
	}
	name_1 = strdup(command.argv[1]);
	argv1[position] = NULL;
	
	for (j; j < command->argc; j++)
	{
		argv2[k] = command.argv[j];
		k++;
	}
	name_2 = strdup(command.argv[position]);
	argv2[command.argc] = NULL;
	
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
			wait(&status);
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
        execvp(name_2, argv_2);
        }
    }
        
	
	
	
	
	
>>>>>>> fac14b6ba92427d03cb25cfd61a9425c2a0d0f8d
	return 0;
}




//Exec(Command *command)
//
//Input:
//	A struct of type Command
//	
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	Nothing
//
//Assumptions:
//	Struct has already been allocated.
//
//This function is the default call when no re-direct or pipe commands were found in the
// input. This function forks and then calls the execvp function with the arguments in the
//	the struct file. Because execvp searches the path, no path searching functionality
//	was included with the calls to execute another process.
//
//
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


//Exec_bg(Command *command)
//
//Input:
//	A struct of type Command
//	
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	Nothing
//
//Assumptions:
//	Struct has already been allocated.
//
//This function is the same as Exec() but does not wait for the process, forcing it to 
//	run in the background.
//
//
int Exec_bg(Command *command)
{
	pid_t pid;
	pid = Fork();
	if (pid == 0)
	{
		execvp(command->name, command->argv);
	}
	
	return 0;
}



//Process(Command *command)
//
//Input:
//	A struct of type Command
//	
//
//Returns:
//	A 0 to indicate successful operation
//
//Modifies:
//	Nothing
//
//Assumptions:
//	Struct has already been allocated.
//
//This function searches the argv field to look for a modifier like < > | or &
//	and calls the appropriate version of Exec().
//
//
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
    		Exec_file_in(command, i);
    		break;
		}
    		
    	if (strcmp(command->argv[i], "|") == 0)
    	{
    		Exec_pipe(command, i);
    		break;
    	}
    	
    	if (strcmp(command->argv[i], "&") == 0)
    	{
    		Exec_bg(command);
    		break;
    	}
    }
    	//no modifiers found, call normal exec()
    	
    	Exec(command);	
    return 0;
}
