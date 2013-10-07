#include "dshell.h"



struct command_t command;

int main(int argc, char *argv[])
{
    int run = 1;
    char *in = NULL;
    pid_t pid;

    Clear_screen();

    while(run)
    {
        printf("%s", PROMPT);
        in = fgets(input, MAX_INPUT-1, stdin);
        if (in != NULL)
        {
        	printf("%s", input);

        	if ((strcmp(input, "exit\n") == 0))
        	{
            	run = 0;
            	break;
        	}

        	Parse(input, &command);

			printf("Command name = %s\n", command.name);
			printf("Argc %d\n", command.argc);
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
          //  execvp(test.command_name, *test.params);
        	exit(0);
        	}

       wait(pid); 
      printf("test");
    }*/
   