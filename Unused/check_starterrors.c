/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:37:44 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/04 12:38:23 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
