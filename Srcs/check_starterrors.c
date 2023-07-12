/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:49:37 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/12 18:57:49 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void error_dquote(char *str, int *dquote, int *i)
{
	*dquote = 1;
	(*i)++;
	while (str[*(i)] != '"')
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
	while (str[*i] != 39)
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
	while (str[i])
	{
		while (str[i] != '"' || str[i] != 39)
			i++;
		if (str[i] == 39)
			error_squote(str, &squote, &i);
		if (str[i] == '"')
			error_dquote(str, &dquote, &i);
	}
	if (squote + dquote > 0)
	{
		printf("quote not closed\n");
		return (-1);
	}
	return (0);
}

int error_bslash(char *str, int i)
{
	while (str[i])
	{
		while (((str[i] != 34) || str[i] != 39) || str[i] != 92)
			i++;
		if (str[i] == 34)
		{
			while (str[++i] != 34)
				i++;
			i++;
		}
		if (str[i] == 39)
		{
			while (str[++i] != 39)
				i++;
			i++;
		}
		if (str[i] == 92)
		{
			printf("error '\\' unknow command\n");
			return (1);
		}
	}
	return (0);
}

int error_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i + 3])
			i++;
		if (((str[i] == '|') || str[i] == '>') || str[i] == '<')
		{
			printf("false redirection\n");
			return (-1);
		}
		else
			return (0);
	}
	return (0);
}

int	check_starterrors(char *str)
{
	int	boole;

	boole = 0;
	boole += error_quote(str);
	boole += error_bslash(str, 0);
	boole += error_pipe(str);
	if (boole > 0)
		return (-1);
	else
		return (0);
}
