/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:05:03 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 06:02:03 by hnogared         ###   ########.fr       */
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

static int	init_pwd(t_env **env_list)
{
	int		status;
	char	pwd[512];
	char	*pwd_arg;
	char	*oldpwd_arg;

	if (!getcwd(pwd, 512))
		return (SH_ERROR);
	if (!ft_getenv(*env_list, "PWD"))
	{
		pwd_arg = ft_strjoin("PWD=", pwd);
		status = export_var(pwd_arg, env_list, SH_OVERWRITE);
		safe_free((void **)&pwd_arg);
		if (status != SH_SUCCESS)
			return (SH_ERROR);
	}
	if (!ft_getenv(*env_list, "OLDPWD"))
	{
		oldpwd_arg = ft_strjoin("OLDPWD=", pwd);
		status = export_var(oldpwd_arg, env_list, SH_OVERWRITE);
		safe_free((void **)&oldpwd_arg);
		if (status != SH_SUCCESS)
			return (SH_ERROR);
	}
	return (SH_SUCCESS);
}

static int	modif_shlvl(t_env **env)
{
	char	*tmp;
	char	*new_lvl;

	if (!env || !*env)
		return (SH_ERROR);
	tmp = ft_getenv(*env, "SHLVL");
	if (!tmp)
		return (ft_export((char *[]){"export", START_SHLVL, NULL}, env));
	new_lvl = ft_itoa(ft_atoi(tmp) + 1);
	if (!new_lvl)
		return (SH_ERROR);
	tmp = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	if (!tmp)
		return (SH_ERROR);
	export_var(tmp, env, SH_OVERWRITE);
	free(tmp);
	return (SH_SUCCESS);
}

t_env	*init_env(t_env **env_list, char **envp)
{
	*env_list = get_default_env(envp);
	if (!ft_getenv(*env_list, "LOGNAME") && ft_export(
			(char *[]){"export", START_LOGNAME, NULL}, env_list) == SH_ERROR)
		return (free_env(env_list), NULL);
	if (!ft_getenv(*env_list, "NAME") && ft_export(
			(char *[]){"export", START_NAME, NULL}, env_list) == SH_ERROR)
		return (free_env(env_list), NULL);
	if (init_pwd(env_list) == SH_ERROR || modif_shlvl(env_list) == SH_ERROR)
		return (free_env(env_list), NULL);
	return (*env_list);
}
