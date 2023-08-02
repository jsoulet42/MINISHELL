/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lentab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:28:48 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/02 01:02:41 by lolefevr         ###   ########.fr       */
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
	t_shell	*temp;
	int	i;

	temp = env;
	i = 0;
	if (!envp)
		return (NULL);
	found = get_env_var(temp->env, "OLDPWD");
	found2 = get_env_var(temp->env, "PWD");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD", 3) == 0)
			envp[i] = found2->name;
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
			envp[i] = found->name;
		i++;
	}
	return (envp);
}
