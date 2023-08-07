/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:22:41 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 15:21:45 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	fusion_arg(char **line)
{
	int	i;

	i = 1;
	easy_quote_utils(line);
	while (i != 0)
	{
		i = 0;
		i += easy_quote(line);
		i += hard_quote_01(line, 0, 0);
		i += hard_quote_02(line);
	}
}

int	hard_quote_01(char **l, int i, int res)
{
	int	start;

	while ((*l)[i])
	{
		if ((*l)[i] == '\"' && i > 1 && ft_is_whitespace((*l)[i - 1]) != 0)
		{
			start = i - 1;
			ft_supprchar(l, i);
			while (start >= 0 && ft_is_whitespace((*l)[start]) != 0)
				start--;
			ft_addchar(l, start, "\"");
			while ((*l)[i] && (*l)[i] != '\"')
				i++;
			res = 1;
		}
		else if ((*l)[i] == '\"' && ft_is_whitespace((*l)[i - 1]) == 0)
		{
			i++;
			while ((*l)[i] && (*l)[i] != '\"')
				i++;
		}
		i++;
	}
	return (res);
}

int	hard_quote_02(char **line)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			i += is_quote(*line + i) + 1;
		if ((*line)[i] == '\"')
		{
			i += is_quote(*line + i) + 1;
			if (ft_is_whitespace((*line)[i + 1]) != 0)
			{
				ft_supprchar(line, i);
				while ((*line)[i] && ft_is_whitespace((*line)[i]) != 0)
					i++;
				ft_addchar(line, i, "\"");
				res = 1;
			}
		}
		i++;
	}
	return (res);
}

int	easy_quote(char **line)
{
	int		i;
	int		res;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"' && (*line)[i + 1] == '\"')
		{
			ft_supprchar(line, i);
			ft_supprchar(line, i);
			i -= 2;
			res = 1;
		}
		i++;
	}
	return (res);
}

void	easy_quote_utils(char **line)
{
	int		i;
	int		tmp;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"')
			i += is_quote_zero(*line + i) + 1;
		if ((*line)[i] == '\'')
		{
			tmp = i;
			i += is_quote_zero(*line + i);
			(*line)[tmp] = '\"';
			(*line)[i] = '\"';
		}
		i++;
	}
}
