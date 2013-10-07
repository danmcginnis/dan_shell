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
        in = fgets(input, MAX_INPUT-1, stdin);
        if (in != NULL)
        {
        	if ((strcmp(input, "exit\n") == 0))
        	{
            	run = 0;
            	return 0;
            	break;
        	}

        	Parse(input, &command);

			printf("Command name = %s\n", command.argv[0]);
			printf("Argc %d\n", command.argc);
			printf("1st argv %s\n", command.argv[1]);
			
			//Process(&command);
			Execvp(&command);
			
    	}
    	}
return 0;
}
    
    
    /*if (in != NULL)
    {
        pid = Fork();
        if (pid == 0) {
        //	sscanf(temp, "%s" , test.command_name);
         //   printf("%s\n", test.command_name);
          //  
        	exit(0);
        	}

       wait(pid); 
      printf("test");
    }*/
   