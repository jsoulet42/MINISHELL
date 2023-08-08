/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:25:31 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 17:00:35 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell	*g_shell_data;

int	init_data(char **envp)
{
	g_shell_data = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!g_shell_data)
		return (1);
	modif_shlvl(envp);
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	return (0);
}

static int	prompt_cmd(char **envp)
{
	char	*line;
	char	*line2;

	if (!envp)
		return (1);
	line = prompt(g_shell_data->env);
	if (!line || !*line)
		return (line2 = line, safe_free((void **)&line), !line2);
	add_history(line);
	line2 = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (check_starterrors(line2) > 0)
		return (free(line2), 1);
	if (prompt_cmd_02(line2, envp))
		return (1);
	return (0);
}

int	prompt_cmd_02(char *line2, char **envp)
{
	int	i;

	free_trinity();
	g_shell_data->t = ft_parsing(line2);
	free(line2);
	if (!g_shell_data->t)
		return (1);
	i = 0;
	while (g_shell_data->t && g_shell_data->t[i + 1])
		piper(g_shell_data->env, g_shell_data->t[i++]);
	if (agent_smith(g_shell_data->t[i]->cmd[0]) != -1)
		execute_builtin(g_shell_data->t[i], g_shell_data->t[i]->builtin);
	else
		exec_last(g_shell_data->env, g_shell_data->t[i], envp);
	safe_free((void **)&g_shell_data->path);
	dup2(g_shell_data->in, STDIN_FILENO);
	dup2(g_shell_data->out, STDOUT_FILENO);
	free_t_par(g_shell_data->par);
	return (0);
}

int	execute_first_builtin(t_rinity *cmd_struct, int builtin)
{
	if (builtin == 1)
	{
		ft_exit();
		return (1);
	}
	else if (builtin == 2)
	{
		ft_export(cmd_struct->cmd, &g_shell_data->env);
		return (1);
	}
	else if (builtin == 3)
	{
		ft_unset(cmd_struct->cmd, &g_shell_data->env);
		return (1);
	}
	else if (builtin == 0)
	{
		ft_cd(lentab(cmd_struct->cmd), cmd_struct->cmd, &g_shell_data->env);
		return (1);
	}
	else
		return (0);
}

/*
 * SIGQUIT -> Ctrl-\ signal which needs to be ignored
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	*test;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, main_sig_handler);
	if (init_data(envp))
		return (1);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	while (1)
	{
		if (prompt_cmd(envp))
			continue ;
		test = g_shell_data;
		envp = env_update(envp, test);
	}
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	return (0);
}
