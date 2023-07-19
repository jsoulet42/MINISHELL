/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mamain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:55:51 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/19 15:33:50 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	char *str[] = {"cd", "yo", NULL};
	char str2[512];

	(void)argc;
	(void)argv;
	pid = fork();
	if (pid == 0)
		execve("./ft_cd", str, env);
	else
	{
		waitpid(pid, NULL, 0);
		printf("%s\n", getcwd(str2, 512));
	}
//	printf("salut\n");
//	printf("%s\n", getcwd(str2, 512));
	return 0;
}
