/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:17:03 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/29 16:29:48 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (!n)
		return (0);
	while (((char *)s1)[i] && ((char *)s1)[i] == ((char *)s2)[i] && --n)
	{
		if (!s1[i])
			return (0);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	else
	{
		perror("Erreur lors du changement de répertoire");
		return (-1);
    }
}

void	update_pwd(char *oldpwd, char *pwd, t_env *env)
{
	t_env	*found;
	t_env	*found2;
	char	*str;
	char	*str2;

	str = ft_strjoin("OLDPWD=", oldpwd);
	str2 = ft_strjoin("PWD=", pwd);
	found = get_env_var(env, "OLDPWD");
	found2 = get_env_var(env, "PWD");
	found->name = str;
	found2->name = str2;
}

void ft_cd(int argc, char **argv, t_env *env)
{
	int		changedir;
	char	*home;
	char	*oldpwd;
	char	*pwd;

	oldpwd = malloc(sizeof(char) * 512);
	pwd = malloc(sizeof(char) * 512);
	getcwd(oldpwd, 512);
	home = ft_getenv(env, "HOME");
	if (!home)
		ft_printf("HOME not set");
	changedir = 42;
	if ((argc < 2 ) || (argv[1][0] == '~'))
	{
		if (home)
			changedir = change_directory(home);
	}
	else
		changedir = change_directory(argv[1]);
	if (changedir == 0)
		printf("Répertoire changé avec succès.\n");
	getcwd(pwd, 512);
	update_pwd(oldpwd, pwd, env);
	free(oldpwd);
	free(pwd);
}
