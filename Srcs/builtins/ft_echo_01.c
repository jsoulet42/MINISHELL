/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:38 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/12 11:10:22 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void ft_echo(char *str, int option, char *stro)
{
	if (option == 1)
		printf("%s", str);
	else if (option == 3)
		printf("%s %s",stro, str);
	else
		printf("%s\n", str);
}

int	main(int argc, char **argv)
{
	if (argc > 1 && argv[1][0] == '-')
	{
		if (argv[1][1] == 'n')
			ft_echo(argv[2], 1, NULL);
		else
			ft_echo(argv[2], 3, argv[1]);
	}
	else
		ft_echo(argv[1], 0, NULL);
	return (0);
}
