/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:13:20 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/08 11:59:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	set_termios_mode(int mode)
{
	struct termios	terminos_opts;

	if (tcgetattr(STDOUT_FILENO, &terminos_opts) < 0)
		return (SH_ERROR);
	if (mode == TERMIOS_MUTE_CTRL)
		terminos_opts.c_lflag &= ~ECHOCTL;
	else
		terminos_opts.c_lflag |= ECHOCTL;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_opts) < 0)
		return (SH_ERROR);
	return (SH_SUCCESS);
}

char	*prompt(t_env *env)
{
	char	*line;
	char	*prompt;

	if (!ft_getenv(env, "LOGNAME") || !ft_getenv(env, "NAME"))
		line = readline("guest@mishelle $> ");
	else
	{
		prompt = expand_dollars("$LOGNAME@$NAME ", g_shell_data->env);
		if (!prompt)
			return (NULL);
		if (!ft_free_strcat(&prompt, "$> ", 0, 4))
			return (safe_free((void **) &prompt), NULL);
		line = readline(prompt);
		free(prompt);
	}
	if (!line)
	{
		ft_printf("mishelle: Exit o7\n");
		free_and_exit();
	}
	return (line);
}
