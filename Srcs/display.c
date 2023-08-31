/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:37:31 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/31 20:05:40 by hnogared         ###   ########.fr       */
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
		ft_exit(0, NULL);
	return (line);
}

void	ft_perror(const char *prefix, const char *prefix2)
{
	char	empty[1];
	char	colon[3];
	char	*res;
	char	*colon_res;

	empty[0] = 0;
	ft_memmove(colon, ": ", 3);
	res = (char *)((uintptr_t)prefix * (1 && prefix)
			+ (uintptr_t)empty * (!prefix));
	colon_res = (char *)((uintptr_t)colon * (1 && prefix)
			+ (uintptr_t)empty * (!prefix));
	ft_fprintf(STDERR_FILENO, "%s%s", res, colon_res);
	res = (char *)((uintptr_t)prefix2 * (1 && prefix2)
			+ (uintptr_t)empty * (!prefix2));
	colon_res = (char *)((uintptr_t)colon * (1 && prefix2)
			+ (uintptr_t)empty * (!prefix2));
	ft_fprintf(STDERR_FILENO, "%s%s", res, colon_res);
	perror(NULL);
}
