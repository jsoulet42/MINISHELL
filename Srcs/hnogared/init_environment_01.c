/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:37:36 by me                #+#    #+#             */
/*   Updated: 2023/07/19 15:20:58 by hnogared         ###   ########.fr       */
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
		new = new_env_var(envp[i++], NULL, NULL);
		if (!new)
			return (free_env(&env_list), NULL);
		env_add_back(&env_list, new);
	}
	return (env_list);
}

static t_env	*complete_env(t_env **env_list)
{
	char	*temp;
	char	*value;

	if (!env_list)
		return (NULL);
	value = ft_getenv(*env_list, "PATH");
	value = ft_strjoin_plus(START_PATH, value);
	if (!value)
		return (NULL);
	temp = ft_strjoin_plus("PATH=", value);
	free(value);
	if (!temp)
		return (NULL);
	ft_export((char *[]){"export", temp, NULL}, env_list);
	free(temp);
	return (*env_list);
}

t_env	*init_env(t_env **env_list, char **envp)
{
	*env_list = get_default_env(envp);
	if (!complete_env(env_list))
		return (free_env(env_list), NULL);
	return (*env_list);
}
