#include "shell.h"

/**
 * info_init - Function that initializes info_t struct
 * @info: struct address
 */
void info_init(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	(*info).path = NULL;
	info->argc = 0;
}

/**
 * info_set - Function that sets info_t struct
 * @info: struct address
 * @av: argument vector
 */
void info_set(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = custom_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		substitute_alias(info);
		substitute_vars(info);
	}
}

/**
 * info_free - unction that frees info_t struct
 * @info: struct address
 * @all: true if all fields are freed
 */
void info_free(info_t *info, int all)
{
	field_freed(info->argv);
	info->argv = NULL;
	(*info).path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		field_freed(info->environ);
			info->environ = NULL;
		buf_freed((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
