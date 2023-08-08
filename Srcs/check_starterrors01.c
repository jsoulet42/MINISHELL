/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:53 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 17:39:35 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	error_dquote(char *str, int *dquote, int *i)
{
	*dquote = 1;
	(*i)++;
	while (str[*(i)] && str[*(i)] != '"')
		(*i)++;
	if (str[*(i)] == '"')
	{
		*dquote = 0;
		(*i)++;
	}
}

void	error_squote(char *str, int *squote, int *i)
{
	*squote = 1;
	(*i)++;
	while (str[*(i)] && str[*i] != 39)
		(*i)++;
	if (str[*i] == 39)
	{
		*squote = 0;
		(*i)++;
	}
}

int	error_quote(char *str)
{
	int	dquote;
	int	squote;
	int	i;

	i = 0;
	squote = 0;
	dquote = 0;
	while (str[i])
	{
		while (str[i] && (str[i] != '"' && str[i] != 39))
			i++;
		if (str[i] == 39)
			error_squote(str, &squote, &i);
		if (str[i] == '"')
			error_dquote(str, &dquote, &i);
	}
	if (squote + dquote > 0)
	{
		printf("Error : quote not closed\n");
		return (1);
	}
	return (0);
}

void	dblequote(int *i, char *str)
{
	(*i)++;
	while (str[*(i)] && str[*(i)] != 34)
		(*i)++;
}

void	simplequote( int *i, char *str)
{
	(*i)++;
	while (str[*(i)] && str[*(i)] != 39)
		(*i)++;
}