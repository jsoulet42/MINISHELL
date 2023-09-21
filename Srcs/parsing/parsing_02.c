/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:22:31 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 06:34:18 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	check_line_words(const char **line_tab)
{
	int		test;
	int		test2;
	char	**temp;

	if (!line_tab || !*line_tab)
		return (SH_ERROR);
	temp = (char **)line_tab - 1;
	while (*(++temp))
	{
		test = ft_isoperand(**temp);
		if (*(temp + 1))
			test2 = ft_isoperand(*(temp + 1)[0]);
		if (test && (!*(temp + 1) || test2))
		{
			printf("mishelle: syntax error bad operand `");
			printf("%s'\n", *temp);
			return (SH_ERROR);
		}
	}
	return (SH_SUCCESS);
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

int	doublequote(int *i, char *str)
{
	int	start;

	if (!i || !str)
		return (0);
	start = *i;
	(*i)++;
	while (str[*(i)] && str[*(i)] != 34)
		(*i)++;
	return (*i - start);
}

int	simplequote(int *i, char *str)
{
	int	start;

	if (!i || !str)
		return (0);
	start = *i;
	(*i)++;
	while (str[*(i)] && str[*(i)] != 39)
		(*i)++;
	return (*i - start);
}
