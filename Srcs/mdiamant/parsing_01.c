/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:09:47 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/13 09:20:34 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int		calcSizeType(char *str);
int		calcType(char *str);
void	sparse(t_par **p, char *argv);

void	ft_parsing(char *argv)
{
	int		res;
	char	*line;
	t_par	**p;

	line = ft_strtrim(argv, " ");

	res = count_arg(line);
	printf("il y a %d mots\n", res);

	p = malloc(sizeof(t_par *) * (res + 2));
	sparse(p, line);
	free(line);
	free_t_par(p);
}

void	sparse(t_par **p, char *argv)
{
	int	i;
	int j;
	int size;

	i = 0;
	j = 0;
	while(argv[i] && argv[i] != '\n')
	{
		i += getSkipCount(argv + i);
		p[j] = malloc(sizeof(t_par));
		if (verifquote(argv + i) == 1)
		{
			p[j]->str = ft_substr(argv, i, 1);
			p[j++]->type = calcType(argv + i);
			size = calcSizeType(argv + i);
			p[j++]->str = ft_substr(argv, i + 1, size);
			i += size + 1;
			p[j]->str = ft_substr(argv, i - 1, 1);
			p[j++]->type = calcType(argv + i - 1);
		}
		else
		{
		p[j]->type = calcType(argv + i);
		size = calcSizeType(argv + i);
		p[j]->str = ft_substr(argv, i, size);
		printf("p[%d] = type : %d, str : '%s'\n", j, p[j]->type, p[j]->str);
		j++;
		i += size;
		}

	}
	p[j] = NULL;
}

int	verifquote(char *argv)
{
	if (argv[0] == '\'' || argv[0] == '\"')
		return (1);
	return (0);
}

void free_t_par(t_par **p)
{
	int i;

	i = 0;
	while (p[i])
	{
		free(p[i]->str);
		free(p[i]);
		i++;
	}
	free(p);
}

int calcType(char *str)
{
	/*if (ft_isalnum(str[0]))
		return (1);
	if (is_operand(str))
		return (3);
	if (str[0] == '\'')
		return (4);
	if (str[0] == '\"')
		return (4);
	if (str[0] == '\n')
		return (0);*/
	if (is_operand(str))
		return (1);
	return (2);
}
int calcSizeType(char *str)
{
	int	size;
	int i;

	i = 0;
	size = 1;
	if (simplquote(str + 1) != -1)
	{
		size = simplquote(str + 1) + 1;
	}
	else if (doublquote(str) != -1)
		size = doublquote(str + 1) + 1;
	else if (is_operand(str) != 0)
		size = is_operand(str);
	else
	{
		while (str[i])
		{
			if (is_operand(str + i) || simplquote(str + i) != -1
			|| doublquote(str + i) != -1 || str[i] == ' ' || str[i] == '\t')
				break;
			i++;
		}
		size = i;
	}
	if (size == 0)
		error_exit("error size = 0 // fonction : calcSizeType // erno ");
	return (size);
}

int count_arg(const char *argv)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 1;
	while (argv[i])
	{
		if (argv[i] == ' ')
		{
			i += getSkipCount(argv + i);
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
			if (argv[i + 1] != ' ' && argv[i + 1] != '\n')
				count++;
		}
		i++;
	}
	return (count);
}

int	is_operand(const char *str)
{
	int res;
	int i;

	res = 0;
	if (ft_strchr(OPERANDS, *str) != NULL && *str != ' ' && *str)
	{
		if (str[0] == str[1])
		{
			res = 2;
			i = 2;
		}
		else
		{
			i = 1;
			res = 1;
		}
		i += getSkipCount(str + i);
		if (is_operand(str + i) != 0)
		{
			printf("error operand : %s, %d\n", str, res);
			error_exit("Robin, sort de ce corps !");
		}
	}
	return (res);
}

int	getSkipCount(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}
