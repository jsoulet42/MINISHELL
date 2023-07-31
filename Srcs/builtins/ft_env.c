/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:06 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/31 16:45:20 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_env(char **env)
{
	int	i;

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
