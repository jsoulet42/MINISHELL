/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:01:30 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/04 14:11:42 by mdiamant         ###   ########.fr       */
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
			break;
		}
		i++;
	}
}
