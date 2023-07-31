/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lentab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:28:48 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/31 15:42:45 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	lentab(char **tableau)
{
	int	i;

	i = -1;
	while(tableau[++i])
		i = i;
	return (i);
}
char	**env_update(char **envp, t_shell *env)
{
	t_env	*found;
	t_env	*found2;
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	found = get_env_var(env->env, "OLDPWD");
	found2 = get_env_var(env->env, "PWD");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			envp[i] = found2->name;
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			envp[i] = found->name;
		i++;
	}
	return (envp);
}
