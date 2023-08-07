/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:02 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 15:31:04 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	else
	{
		perror("Erreur lors du changement de répertoire");
		return (-1);
	}
}

t_env	*update_pwd(char *oldpwd, char *pwd, t_env **env)
{
	t_env	*found;
	t_env	*test;

	found = g_shell_data->env;
	found = get_env_var(found, "PWD");
	found->value = pwd;
	found = get_env_var(found, "OLDPWD");
	found->value = oldpwd;
	test = *env;
	test = get_env_var(test, "PWD");
	return (*env);
}

struct s_cd
{
	int		changedir;
	char	*home;
	char	*oldpwd;
	char	*pwd;
	t_env	*envi;
	t_env	*envtest;
};

t_env	*ft_cd(int argc, char **argv, t_env **env)
{
	struct s_cd		cd;

	cd.envtest = *env;
	cd.envi = *env;
	cd.oldpwd = malloc(sizeof(char) * 512);
	cd.pwd = malloc(sizeof(char) * 512);
	getcwd(cd.oldpwd, 512);
	cd.home = ft_getenv(cd.envi, "HOME");
	cd.changedir = 42;
	if ((argc < 2) || (argv[1][0] == '~'))
	{
		if (cd.home)
			cd.changedir = change_directory(cd.home);
		else
		{
			ft_printf("HOME not set");
			return (*env);
		}
	}
	else
		cd.changedir = change_directory(argv[1]);
	if (cd.changedir == 0)
		cd.envtest = update_pwd(cd.oldpwd, getcwd(cd.pwd, 512), env);
	return (cd.envtest);
}
