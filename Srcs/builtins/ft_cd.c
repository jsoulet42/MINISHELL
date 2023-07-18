/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:17:03 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/17 15:41:53 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*char *str[] = {"cd", NULL};*/
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
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			break ;
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

void ft_cd(int argc, char **argv, char **env)
{
	int		changedir;
	char	*home;
	int i = -1;

	changedir = 42;
	printf("argc = %d\n", argc);
	while (argv[++i])
		printf("argv = %s   ok \n", argv[i]);
	if (argc < 2)
	{
		home = go_home(env);
		changedir = change_directory(home);
		free(home);
	}
	else
		changedir = change_directory(argv[1]);
	if (changedir == 0)
		printf("Répertoire changé avec succès.\n");
	return ;
	// ok
}
