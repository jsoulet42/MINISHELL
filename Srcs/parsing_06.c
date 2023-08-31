/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_06.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:24:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/30 21:59:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_quote(char *argv)
{
	if (argv[0] == '\'')
		return (simplquote(argv + 1));
	else if (argv[0] == '"')
		return (doublquote(argv + 1));
	return (-1);
}

int	is_quote_zero(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] == '\'')
	{
		while (argv[i])
		{
			if ((int)argv[i] == 39)
				return (i);
			i++;
		}
	}
	else if (argv[0] == '"')
	{
		while (argv[i])
		{
			if ((int)argv[i] == 34)
				return (i);
			i++;
		}
	}
	return (0);
}

int	verifquote(char *argv)
{
	if (argv[0] == '\'' || argv[0] == '\"')
		return (1);
	return (0);
}

int	next_pipe(char **line_tab)
{
	int	j;

	if (!line_tab)
		return (0);
	j = 0;
	while (line_tab[j] && line_tab[j][0] != '|')
		j++;
	return (j);
}

int	real_cmd(char **line_tab)
{
	int	i;

	if (!line_tab)
		return (0);
	i = 1;
	while (*line_tab)
		i += ((*line_tab++)[0] == '|');
	return (i);
}
