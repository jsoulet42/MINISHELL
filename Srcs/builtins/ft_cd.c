/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:17:03 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/25 19:23:49 by jsoulet          ###   ########.fr       */
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

char	*go_home(char **env)
{
	char	*home;
	int		i;
	int		j;

	j = 0;
	i = -1;

	while (env[++i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			break ;
		else
		{
			ft_printf("HOME not set\n");
			return (NULL);
		}
	}
	while (env[i][5 + j])
		j++;
	home = malloc(sizeof(char) * j + 1);
	j = 0;
	while (env[i][5 + j])
	{
		home[j] = env[i][5 + j];
		j++;
	}
	return (home);
}

void ft_cd(int argc, char **argv, t_env *env)
{
	int		changedir;
	char	*home;

	changedir = 42;
	if (argc < 2)
	{
		home = ft_getenv(env, "HOME");
		if (home)
			changedir = change_directory(home);
	}
	else
		changedir = change_directory(argv[1]);
	if (changedir == 0)
		printf("Répertoire changé avec succès.\n");
}
