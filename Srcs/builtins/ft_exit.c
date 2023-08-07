#include "../../Includes/minishell.h"

void ft_exit()
{
	free_trinity();
	safe_free((void **)&g_shell_data->path);
	if (g_shell_data->env)
		free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	exit(EXIT_SUCCESS);
}
