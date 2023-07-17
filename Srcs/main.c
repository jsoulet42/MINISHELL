/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/17 17:06:51 by hnogared         ###   ########.fr       */
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
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	return (0);
}

static int	prompt_cmd(void)
{
	char	*line;
	char	*line2;

	dup2(g_shell_data->in, STDIN_FILENO);
	dup2(g_shell_data->out, STDOUT_FILENO);
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
	piper(g_shell_data->par, g_shell_data->env);
	free_t_par(g_shell_data->par);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**test = (char *[]){"export", "COUCOU+=45", NULL};
	(void)argc;
	(void)argv;
	if (init_data(envp))
		return (1);
	ft_export(test, g_shell_data->env);
	print_env(g_shell_data->env, SH_UNORDERED);
	while (1)
	{
		if (prompt_cmd())
			return (free_data(g_shell_data), 1);
	}
	free_env(&g_shell_data->env);
	return (0);
}
