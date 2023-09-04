/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:17:00 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 12:42:34 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static unsigned char	error_quote(char *str)
{
	unsigned char	quote;

	if (!str)
		return (1);
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && (quote == 0 || quote == *str))
			quote = (quote == 0) * *str;
		str++;
	}
	return (quote);
}

static int	viveldop(char gel, char *str, int *i)
{
	if (str[*(i) + 1] == gel)
		return (1);
	return (0);
}

static int	error_gen(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 34)
			doublequote(&i, str);
		if (str[i] == 39)
			simplequote(&i, str);
		if ((((str[i] == 92) || str[i] == 40) || str[i] == 59) || str[i] == 41)
			return (i);
		if ((str[i] == '&' || str[i] == '|') && (viveldop(str[i], str, &i) > 0))
			return (i);
		i++;
	}
	return (0);
}

static int	error_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] != 0)
		i++;
	if (((str[i] == '|') || str[i] == '>') || str[i] == '<')
		return (i);
	return (0);
}

int	check_starterrors(char *str)
{
	int	status;

	status = (int)error_quote(str);
	if (status)
	{
		ft_printf("mishelle: Unterminated quote `%c'\n", (unsigned char)status);
		return (1);
	}
	status = error_gen(str, 0);
	if (status)
	{
		printf("mishelle: Syntax error near unexpected `%c'\n", str[status]);
		return (1);
	}
	status = error_pipe(str);
	if (status)
	{
		printf("mishelle: Redirection error near `%c'\n", str[status]);
		return (1);
	}
	return (0);
}
