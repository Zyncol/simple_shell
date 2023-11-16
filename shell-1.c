#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    info_t info = INFO_INIT;

    while (1)
    {
        printf("%s", "#cisfun$ ");

        if (get_input(&info) == -1)
            break;

        if (info.arg == NULL)
            break;

       info.arg[_strlen(info.arg) - 1] = '\0';

        pid_t pid;

	if ((pid = fork()) == -1)
	{
    	perror("fork");
  	  break;
	}
        if (pid == 0)
        {
           
            find_cmd(&info);
            exit(info.status);
	}
    
        else
        {
            waitpid(pid, &(info.status), 0);
        }

        free_info(&info, 0);
    }

    free_info(&info, 1);
    return 0;
}

