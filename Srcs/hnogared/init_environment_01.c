/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:37:36 by me                #+#    #+#             */
/*   Updated: 2023/07/31 16:10:29 by jsoulet          ###   ########.fr       */
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

static t_env	*complete_env_path(t_env **env_list)
{
	char	*temp;
	char	*value;

	if (!env_list)
		return (NULL);
	value = ft_getenv(*env_list, "PATH");
	value = ft_strjoin_plus(START_PATH, value);
	if (!value)
		return (NULL);
	temp = ft_strtrim(value, ":");
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
	if (!complete_env_path(env_list))
		return (free_env(env_list), NULL);
	if (!ft_getenv(*env_list, "LOGNAME") && ft_export(
			(char *[]){"export", START_LOGNAME, NULL}, env_list) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*env_list, "NAME") && ft_export(
			(char *[]){"export", START_NAME, NULL}, env_list) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*env_list, "HOME") && ft_export(
			(char *[]){"export", START_HOME, NULL}, env_list) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*env_list, "SHLVL") && ft_export(
			(char *[]){"export", START_SHLVL, NULL}, env_list) == SH_ERROR)
		return (NULL);
	if(!ft_getenv(*env_list, "PWD") && ft_export(
			(char *[]){"export", START_PWD, NULL}, env_list) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*env_list, "OLDPWD") && ft_export(
			(char *[]){"export", START_OLDPWD, NULL}, env_list) == SH_ERROR)
		return (NULL);
	return (*env_list);
}
