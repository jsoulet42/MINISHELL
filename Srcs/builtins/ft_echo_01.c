/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:12 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 15:31:34 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	print_str_tab_echo(char **str_tab)
{
	if (!str_tab)
	{
		printf("NULL\n");
		return ;
	}
	while (*str_tab)
	{
		printf("%s", *str_tab++);
		if (*str_tab)
			printf(" ");
	}
}

void	ft_echo2(char **str, int option)
{
	if (!str[0] && option == 1)
		return ;
	else if (option == 0)
	{
		print_str_tab_echo(str);
		printf("\n");
	}
	else if (option == 1)
		print_str_tab_echo(str);
}

int	ft_echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	if (argc > 1 && argv[1][0] == '-')
	{
		if (argv[1][i] == 'n')
		{
			while (argv[1][i] && argv[1][i] == 'n')
				i++;
			if (argv[1][i] == '\0')
				ft_echo2(argv + 2, 1);
			else
				ft_echo2(argv + 1, 0);
		}
	}
	else
		ft_echo2(argv + 1, 0);
	return (0);
}
