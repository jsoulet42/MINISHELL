/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:14:32 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/14 17:18:02 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	char *str[] = {"cd", NULL};
	execve("./ft_cd", str, env);
	printf("shelle\n");
	return 0;
}
