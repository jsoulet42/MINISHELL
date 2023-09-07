/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_05.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:24:21 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/30 20:49:41 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	calc_type(char *str)
{
	if (str[0] == '|')
		return (1);
	if (str[0] == '<' && str[1] != '<')
		return (2);
	if (str[0] == '>' && str[1] != '>')
		return (3);
	if (str[0] == '>' && str[1] == '>')
		return (4);
	if (str[0] == '<' && str[1] == '<')
		return (5);
	if (str[0] == ';')
		return (6);
	if (str[0] == '&')
		return (7);
	return (0);
}

int	calc_size_type(char *str)
{
	int	size;
	int	i;

	i = 1;
	size = 1;
	if (is_operand(str) != 0)
		size = is_operand(str);
	else
	{
		while (str[i])
		{
			if (is_operand(str + i) || !ft_is_whitespace(str[i]))
				break ;
			i++;
		}
		size = i;
	}
	return (size);
}

int	count_arg(const char *argv, int i)
{
	int	j;
	int	count;

	count = 1;
	while (argv[i++])
	{
		if (argv[i] == ' ')
		{
			i += get_skip_count(argv + i);
			if (is_operand(argv + i) == 0)
				count++;
		}
		j = is_operand(argv + i);
		if (j != 0)
		{
			if (i == 0)
				count -= 2;
			count++;
			i = i + j - 1;
			if (argv[i + 1] != ' ' && argv[i + 1] != '\t' && argv[i + 1])
				count++;
		}
	}
	return (count);
}

int	is_operand(const char *str)
{
	if (*str && ft_strchr(OPERANDS, *str) != NULL && *str != ' ')
	{
		if (str[0] == str[1])
			return (2);
		return (1);
	}
	return (0);
}

int	get_skip_count(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32 || str[i] == 127)
		i++;
	return (i);
}
