/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:09:47 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/14 17:18:26 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_par	**ft_parsing(char *argv)
{
	int		res;
	char	*line;
	t_par	**p;

	line = ft_strtrim(argv, " ");
	res = count_arg(line);
	p = malloc(sizeof(t_par *) * (res + 2));
	if (!p)
		printf("malloc error // ft_parsing\n");
	sparse(p, line);
	print_t_par(p);
	test_dup(p);
	free(line);
	return (p);
}

void	print_t_par(t_par **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		printf("p[%d]->str : %s\n", i, p[i]->str);
		i++;
	}
}

int	is_quote(char *argv)
{
	if (argv[0] == '\'')
		return (simplquote(argv + 1));
	else if (argv[0] == '"')
		return (doublquote(argv + 1));
	return (-1);
}

void	sparse(t_par **p, char *argv)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (argv[i])
	{
		i += get_skip_count(argv + i);
		p[j] = malloc(sizeof(t_par));
		p[j]->quote_type = 2;
		if (is_quote(argv + i) != -1)
		{
			if (argv[i] == '\'')
				p[j]->quote_type = 1;
			size = is_quote(argv + i);
			if (size == 0)
				p[j]->str = ft_strdup("\0");
			else
				p[j]->str = ft_substr(argv, i + 1, size);
			p[j++]->type = 0;
			i += 2;
		}
		else
		{
			size = calc_size_type(argv + i);
			p[j]->type = calc_type(argv + i);
			p[j++]->str = ft_substr(argv, i, size);
		}
		i += size;
	}
	p[j] = NULL;
}

int	verifquote(char *argv)
{
	if (argv[0] == '\'' || argv[0] == '\"')
		return (1);
	return (0);
}

void	free_t_par(t_par **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]->str);
		free(p[i]);
		i++;
	}
	free(p);
}

int	calc_type(char *str)
{
	if (str[0] == '|')
		return (1);
	else if (str[0] == '<' && str[1] != '<')
		return (2);
	else if (str[0] == '>' && str[1] != '>')
		return (3);
	else if (str[0] == '>' && str[1] == '>')
		return (4);
	else if (str[0] == '<' && str[1] == '<')
		return (5);
	else if (str[0] == ';')
		return (6);
	else if (str[0] == '&')
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
			if (is_operand(str + i) || str[i] == ' ' || str[i] == '\t')
				break ;
			i++;
		}
		size = i;
	}
	if (size == 0)
		error_exit("error size = 0 // fonction : calc_size_type // erno ");
	return (size);
}

int	count_arg(const char *argv)
{
	int	i;
	int	j;
	int	count;

	i = 0;
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
	if (ft_strchr(OPERANDS, *str) != NULL && *str != ' ' && *str)
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
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}
void	test_dup(t_par **p);
{
	int	oldfd;
	int	newfd;

	oldfd = dup(STDIN_FILENO);
	newfd = dup(STDOUT_FILENO);
	printf("oldfd : %d\n", oldfd);
	printf("newfd : %d\n", newfd);

}

