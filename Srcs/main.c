/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 16:04:28 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
//	char	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	print_env(env);
	free_env(&env);
/*	while (1)
	{
		line = prompt();
		if (!line)
			break ;
		ft_parsing(line);
	}
*/	return (0);
}
