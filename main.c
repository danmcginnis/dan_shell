#include "dshell.h"


struct command_t command;

int main(int argc, char *argv[])
{
    
    int run = 1;
    char *in = NULL;
    
    Clear_screen();

    while(run)
    {
        printf("%s", PROMPT);
        in = fgets(input, MAX_INPUT, stdin);
        if (in != NULL)
        {
        	if ((strcmp(input, "exit\n") == 0))
        	{
            	run = 0;
            	return 0;
            	break;
        	}

       	Parse(input, &command);
		Process(&command);			
    	}
	}
return 0;
}
    
   