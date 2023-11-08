#include "shell.h"

/**
 * execute - executing function
 * @argv: argument variable
 * Return: 1 if sucessful
 */

int execute(char **argv)
{
	char *str, cmd[128] = "/usr/bin/";
	pid_t pid;
	char *env[] = {NULL};

	if (cmd == NULL)
	{
		return (0);
		perror("Error no command");
	}
	if (strcmp(argv[0], "exit") == 0)
	{
		return (0);
	}
	str = argv[0];
	strcat(cmd, str);
	if (!argv)
	{
		return (0);
		exit(1);
		perror("Error");
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, argv, env) == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	else
	{
		wait(NULL);
	}
	return (1);
}
