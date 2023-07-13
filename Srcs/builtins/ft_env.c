/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:06 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/12 15:03:50 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	main(int argc, char **env)
{
	int	i;

	i = -1;
	(void)argc;
	if (!env)
		printf("\n");
	else
		while (env[++i])
			printf("%s\n", env[i]);
	return (0);
}
