//////////////////////////////////////////////////////////
//Dan McGinnis
//mcginnis.dan@gmail.com
//CIS 3207 Fall 2013
//Lab 2 October 9, 2013
//"Bash" style shell
//
////////////////////////////////////////////////////////////


#include "dshell.h"



//This function displays the prompt and accepts user input, then passes
//	that input to the parsing and processing functions for the actual
//	work of the program.
//
//


int main(int argc, char *argv[])
{
    
    int run = 1;

    Clear_screen();

    while(run)
    {
    	Command *command = (Command*)malloc(sizeof(Command)) ;
    	command->argc = 0;
    	Command *com_ptr = command;
    	
        printf("%s", PROMPT);
        
        fgets(input, MAX_INPUT, stdin);
        if ((strcmp(input, "exit\n") == 0))
    	{
        	run = 0;
           	return 0;
     	}
       	Parse(input, com_ptr);
		wait(Process(com_ptr));	
		
	}
return 0;
}
    
   