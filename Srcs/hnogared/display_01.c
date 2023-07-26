/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:23:02 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/24 11:35:11 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
	char	*temp;
	char	*prompt;

	if (!ft_getenv(env, "LOGNAME") || !ft_getenv(env, "NAME"))
		return (readline("guest@mishelle $> "));
	temp = expand_dollars("$LOGNAME@$NAME ", g_shell_data->env);
	if (!temp)
		return (NULL);
	prompt = ft_strjoin_plus(temp, "$> ");
	free(temp);
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		ft_printf("mishelle: Exit o7\n");
		free_and_exit();
	}
	return (line);
}
