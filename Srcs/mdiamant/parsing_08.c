/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_08.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:25:23 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 13:25:25 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_is_whitespace(char str)
{
	if (!str)
		return (0);
	if ((str > 8 && str < 14) || str == 32 || str == 127)
		return (0);
	return (1);
}

int	find_next_char(const char *str, const char c)
{
	int	i;

	if (!*str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}

static t_par	*sparse_utils_01(char *argv, int *i, int *size)
{
	t_par	*p;

	p = (t_par *) malloc(sizeof(t_par));
	if (!p)
		return (NULL);
	p->fusion = 0;
	*size = is_quote(argv + *i);
	if (*size == 0)
		p->str = ft_strdup("\0");
	else
		p->str = ft_substr(argv, *i + 1, *size);
	p->type = 0;
	*i += 2;
	return (p);
}

static t_par	*sparse_utils_02(char *argv, int *i, int *size)
{
	t_par	*p;

	p = (t_par *) malloc(sizeof(t_par));
	if (!p)
		return (NULL);
	p->fusion = 0;
	*size = calc_size_type(argv + *i);
	p->type = calc_type(argv + *i);
	p->str = ft_substr(argv, *i, *size);
	return (p);
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
		if (is_quote(argv + i) != -1)
			p[j++] = sparse_utils_01(argv, &i, &size);
		else
			p[j++] = sparse_utils_02(argv, &i, &size);
		i += size;
	}
	p[j] = NULL;
}
