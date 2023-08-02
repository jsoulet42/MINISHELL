/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:37:36 by me                #+#    #+#             */
/*   Updated: 2023/08/02 01:41:51 by lolefevr         ###   ########.fr       */
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
	t_env	**temp;

	temp = env_list;
	*temp = get_default_env(envp);
	if (!complete_env_path(temp))
		return (free_env(temp), NULL);
	if (!ft_getenv(*temp, "LOGNAME") && ft_export(
			(char *[]){"export", START_LOGNAME, NULL}, temp) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*temp, "NAME") && ft_export(
			(char *[]){"export", START_NAME, NULL}, temp) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*temp, "SHLVL") && ft_export(
			(char *[]){"export", START_SHLVL, NULL}, temp) == SH_ERROR)
		return (NULL);
	if(!ft_getenv(*temp, "PWD") && ft_export(
			(char *[]){"export", modif_pwd(), NULL}, temp) == SH_ERROR)
		return (NULL);
	if (!ft_getenv(*temp, "OLDPWD") && ft_export(
			(char *[]){"export", modif_pwd2(), NULL}, temp) == SH_ERROR)
		return (NULL);
	return (*temp);
}

char	*modif_pwd(void)
{
	char *pwd;
	char *tmp_pwd;


	pwd = ft_pwd2();
	if (!pwd)
		return (NULL);
	tmp_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	pwd = NULL;
	if (!tmp_pwd)
		return (NULL);
	return (tmp_pwd);
}

char *ft_pwd2(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	return (pwd);
}

char	*modif_pwd2(void)
{
	char *pwd;
	char *tmp_pwd;


	pwd = ft_pwd2();
	if (!pwd)
		return (NULL);
	tmp_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	pwd = NULL;
	if (!tmp_pwd)
		return (NULL);
	return (tmp_pwd);
}
