/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:12 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/02 00:20:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	index_after_option(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j++] == '-')
		{
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j] && argv[i][j] != 'n')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (0);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	string_index;	

	i = 1;
	if (argc == 1)
	{
		ft_printf("\n");
		return (0);
	}
	string_index = index_after_option(argv);
	while (argc > 1 && argv[i])
	{
		if (i >= string_index)
		{
			ft_printf("%s", argv[i]);
			if (i < argc - 1)
				ft_printf(" ");
		}
		i++;
	}
	if (!(argc > 1 && string_index > 1))
		ft_printf("\n");
	return (0);
}

/*
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
}*/
