/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 16:14:51 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell *g_shell_data;

int	main(void)
{
	char	*line;
	char	*line2;

	g_shell_data = init_fd();
	while (1)
	{
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

int init_fd(void)
{
	g_shell_data = (t_shell *)malloc(sizeof(t_shell));
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	return (0);
}
