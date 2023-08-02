#include "../../Includes/minishell.h"

void	main_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_fprintf(STDERR_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGTERM)
		free_and_exit();
}

void	parent_sig_handler(int signal)
{
	if (signal == SIGINT)
		ft_fprintf(STDERR_FILENO, "\b^C\n");
	if (signal == SIGQUIT)
		ft_fprintf(STDERR_FILENO, "\b^\\Quit\n");
}
