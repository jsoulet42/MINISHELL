/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:37:36 by me                #+#    #+#             */
/*   Updated: 2023/07/17 12:41:48 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static t_env	*get_default_env(char **envp)
{
	int		i;
	t_env	*new;
	t_env	*env_list;

	if (!envp || !*envp)
		return (NULL);
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new = new_env_var(envp[i++], NULL);
		if (!new)
			return (free_env(&env_list), NULL);
		env_add_back(&env_list, new);
	}
	return (env_list);
}

static t_env	*complete_env(t_env **env_list)
{
	char	*temp;
	char	*temp2;
	t_env	*env_var;

	if (!env_list)
		env_list = (t_env **) ft_calloc(1, sizeof(t_env *));
	env_var = get_env_var(*env_list, "PATH");
	if (env_var && !update_env_var(env_var, START_PATH, SH_ADDFRONT))
		return (NULL);
	else if (!env_var)
	{
		temp = ft_strtrim(START_PATH, ":");
		if (!temp)
			return (NULL);
		temp2 = ft_strjoin("PATH=", temp);
		free(temp);
		if (!temp2)
			return (NULL);
		env_var = new_env_var(temp2, NULL);
		if (!env_var)
			return (NULL);
		env_add_back(env_list, env_var);
	}
	return (*env_list);
}

t_env	*init_env(t_env **env_list, char **envp)
{
	*env_list = get_default_env(envp);
	return (complete_env(env_list));
}
