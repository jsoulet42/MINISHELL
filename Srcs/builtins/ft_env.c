/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:06 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/19 16:30:06 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int	i;

	i = -1;
	(void)argc;
	(void)argv;
	if (!env)
		printf("no env\n");
	else
		while (env[++i])
			printf("%s\n", env[i]);
	return (0);
}
