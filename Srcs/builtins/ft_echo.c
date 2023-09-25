/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:10:12 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/25 15:11:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	index_after_option(char **argv, int *no_newline)
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
			if (!ft_is_whitespace(argv[i][j]))
				return (i - 1);
			else
				*no_newline = 1;
		}
		else
			return (i - 1);
		i++;
	}
	return (i);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	string_index;
	int	no_newline;

	i = 1;
	if (argc == 1)
	{
		ft_printf("\n");
		return (0);
	}
	no_newline = 0;
	string_index = index_after_option(argv, &no_newline);
	while (argc > 1 && argv[i])
	{
		if (i > string_index || (string_index == 0 && !no_newline))
		{
			ft_printf("%s", argv[i]);
			if (i < argc - 1)
				ft_printf(" ");
		}
		i++;
	}
	if (!no_newline)
		ft_printf("\n");
	return (0);
}
