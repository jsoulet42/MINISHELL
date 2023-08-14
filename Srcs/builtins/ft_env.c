/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:09:46 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/14 20:03:43 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_env(int argc, char **argv, char **env)
{
	int		i;

	(void)argc;
	(void)argv;
	if (!env)
		return (1);
	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
	}
	return (0);
}
