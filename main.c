#include "shell.h"

/**
 * main - entry point to program
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_stdout(av[0]);
				e_stdout(": 0: Can't open ");
				e_stdout(av[1]);
				e_stdout_char('\n');
				e_stdout_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	env_list_fill(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
