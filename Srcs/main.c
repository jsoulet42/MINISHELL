/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:25:31 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/05 15:51:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell	*g_shell_data;

static int	init_data(char **envp)
{
	g_shell_data = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!g_shell_data)
		return (SH_ERROR);
	modif_shlvl(envp);
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	return (SH_SUCCESS);
}

static int	prompt_and_execute(char **envp)
{
	int		i;
	int		status_code;
	char	*line;
	char	*line2;

	if (!envp || !*envp)
		return (SH_ERROR);
	line = prompt(g_shell_data->env);
	if (!line || !*line)
		return (line2 = line, safe_free((void **)&line), !line2);
	add_history(line);
	line2 = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	free_trinity_tab(g_shell_data->t);
	g_shell_data->t = ft_parsing(line2);
	free(line2);
	if (!g_shell_data->t)
		return (SH_ERROR);
	i = 0;
	status_code = 0;
	while (!status_code && g_shell_data->t && g_shell_data->t[i + 1])
		status_code = piper(g_shell_data->env, g_shell_data->t[i++]);
	if (!status_code)
		exec_last(g_shell_data->env, g_shell_data->t[i], envp);
	return (SH_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*test;

	(void)argc;
	(void)argv;
	if (init_data(envp))
		return (1);
	while (1)
	{
		dup2(g_shell_data->in, STDIN_FILENO);
		dup2(g_shell_data->out, STDOUT_FILENO);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, main_sig_handler);
		if (prompt_and_execute(envp))
			continue ;
		test = g_shell_data;
		envp = env_update(envp, test);
	}
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	free_data(g_shell_data);
	return (0);
}
