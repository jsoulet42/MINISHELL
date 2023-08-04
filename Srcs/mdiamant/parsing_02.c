#include "../../Includes/minishell.h"

int	ft_is_whitespace(char str)
{
	if (!str)
		return (0);
	if ((str > 8 && str < 14) || str == 32 || str == 127 || str == 0)
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

t_par	**sparse(char *argv)
{
	int		i;
	int		j;
	int		size;
	t_par	**p;

	p = (t_par **) malloc(sizeof(t_par *) * (count_arg(argv, 0) + 1));
	if (!p)
		return (NULL);
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
	return (fusion_sparse(p));
}

int	tparlen(t_par **p)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (p[i])
	{
		if (p[i + 1] && p[i]->fusion == 1 && p[i]->type == 0
			&& p[i + 1]->type == 0)
			res--;
		res++;
		i++;
	}
	ft_fprintf(2, "tparlen = %d\n", res);
	return (res);
}
