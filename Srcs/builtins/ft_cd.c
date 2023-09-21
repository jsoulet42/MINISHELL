/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:02 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 15:32:52 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	update_pwd(char *oldpwd, char *pwd, t_env **env)
{
	char	*pwd_arg;
	char	*oldpwd_arg;

	if (!oldpwd || !pwd || !env || !*env)
		return (SH_ERROR);
	pwd_arg = ft_strjoin("PWD=", pwd);
	if (!pwd_arg)
		return (SH_ERROR);
	oldpwd_arg = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_arg)
		return (free(pwd_arg), SH_ERROR);
	ft_export((char *[]){"ft_export", pwd_arg, oldpwd_arg, NULL}, env);
	free(pwd_arg);
	free(oldpwd_arg);
	return (SH_SUCCESS);
}

static int	change_directory(const char *path, t_env **env)
{
	char	pwd[512];
	char	oldpwd[512];

	if (!path || !getcwd(oldpwd, 512) || chdir(path) || !getcwd(pwd, 512))
		return (SH_ERROR);
	return (update_pwd(oldpwd, pwd, env));
}

int	ft_cd(int argc, char **argv, t_env **env)
{
	char	*path;

	if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: cd: too many arguments\n");
		return (SH_ERROR);
	}
	if (argc == 1 || !ft_strncmp(argv[1], "~", 2))
	{
		path = ft_getenv(*env, "HOME");
		if (!path)
			return (ft_fprintf(2, "mishelle: cd: HOME not set\n"), SH_ERROR);
	}
	else if (!ft_strncmp(argv[1], "-", 2))
	{
		path = ft_getenv(*env, "OLDPWD");
		if (!path)
			return (ft_fprintf(2, "mishelle: cd: OLDPWD not set\n"), SH_ERROR);
	}
	else
		path = argv[1];
	if (change_directory(path, env) != SH_SUCCESS)
		return (ft_perror("mishelle: cd", argv[1]), SH_ERROR);
	return (SH_SUCCESS);
}
