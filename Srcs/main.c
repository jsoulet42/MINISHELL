/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 17:52:10 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell *g_shell_data;

int init_fd(char **envp)
{
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*line2;

	(void)argc;
	(void)argv;
	g_shell_data = (t_shell *)malloc(sizeof(t_shell));
	init_fd(envp);
	while (1)
	{
		dup2(g_shell_data->in, STDIN_FILENO);
		dup2(g_shell_data->out, STDOUT_FILENO);
		line = prompt();
		if (!line)
			break ;
		line2 = ft_strtrim(line, " \n\t\v");
		free(line);
		if (check_starterrors(line2) > 0)
			return (0);
		g_shell_data->par = ft_parsing(line2);
		check_line(g_shell_data->par);
		piper(g_shell_data->par, g_shell_data->env);
		free(line2);
		free_t_par(g_shell_data->par);
	}
	return (0);
}
