/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:22:31 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 05:35:46 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
