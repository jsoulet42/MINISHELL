
#include "../../Includes/minishell.h"

void	free_and_return(void)
{
	free_trinity();
	if (g_shell_data)
		free_data(g_shell_data);
	set_termios_mode(TERMIOS_UNMUTE_CTRL);

}
