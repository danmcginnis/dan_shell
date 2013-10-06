#include "dshell.h"

int main(int argc, char *argv[])
{
    int run = 1;
    char temp[MAX_INPUT];
    char *in = NULL;
    pid_t pid;
    
    while(run)
    {
    
    printf("%s", PROMPT);
    commands test = {.params[1] = 0};
    in = fgets(temp, MAX_INPUT-1, stdin);
    if (in != NULL)
    {
        printf("%s\n", temp);
        pid = Fork();
        if (pid == 0) {
        	sscanf(temp, "%s %s", test.command_name, test.params);
        	printf("%s\n", test.command_name);
        	printf("%s\n", test.params);
        	exit(0);
        	}

        
    }
    }
    return 0;

}
