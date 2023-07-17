/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/17 16:11:11 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell	*g_shell_data;

int	init_data(char **envp)
{
	g_shell_data = (t_shell *) malloc(sizeof(t_shell));
	if (!g_shell_data)
		return (1);
	init_env(&g_shell_data->env, envp);
	//g_shell_data->in = dup(STDIN_FILENO);
	//g_shell_data->out = dup(STDOUT_FILENO);
	g_shell_data->fd[0] = 0;
	g_shell_data->fd[1] = 0;
	return (0);
}

static int	prompt_cmd(void)
{
	char	*line;
	char	*line2;
	int		cmd;

	//dup2(g_shell_data->in, STDIN_FILENO);
	//dup2(g_shell_data->out, STDOUT_FILENO);
	dup2(g_shell_data->fd[0], STDIN_FILENO);
	line = prompt();
	if (!line)
		return (1);
	line2 = ft_strtrim(line, " \n\t\v");
	free(line);
	if (check_starterrors(line2) > 0)
		return (free(line2), 1);
	g_shell_data->par = ft_parsing(line2);
	free(line2);
	check_line(g_shell_data->par);
	cmd = count_cmd(g_shell_data->par);
	while (cmd > 0)
	{
		piper(g_shell_data->par, g_shell_data->env);
		cmd--;
	}
	free_t_par(g_shell_data->par);
	return (0);
}

int count_cmd(t_par **par)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (par[i])
	{
		if (par[i]->commande_elem_id == 1)
			j++;
		i++;
	}
	return (j);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (init_data(envp))
		return (1);
	while (1)
	{
		if (prompt_cmd())
			return (free_data(g_shell_data), 1);
	}
	free_env(&g_shell_data->env);
	return (0);
}
