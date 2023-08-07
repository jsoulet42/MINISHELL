/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:17:42 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 13:17:44 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	new_shlvl(char *env)
{
	int	sh_atoi;

	sh_atoi = ft_atoi(env + 6);
	if (sh_atoi <= 9)
		*(env + 6) += 1;
}

void	modif_shlvl(char **env)
{
	int	i;

	i = 0;
	if (!*env)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			new_shlvl(env[i]);
			break ;
		}
		i++;
	}
}
