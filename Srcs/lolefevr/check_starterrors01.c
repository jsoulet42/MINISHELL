/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:49:37 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/13 17:33:09 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void error_dquote(char *str, int *dquote, int *i)
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

void error_squote(char *str, int *squote, int *i)
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
void dblequote(int *i, char *str)
{
	(*i)++;
	while (str[*(i)] && str[*(i)] != 34)
		(*i)++;
}
void simplequote( int *i, char *str)
{
	(*i)++;
	while (str[*(i)] && str[*(i)] != 39)
		(*i)++;
}


