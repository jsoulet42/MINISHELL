#include "../../Includes/minishell.h"

static int	tparlen(t_par **p);
static t_par	**fusion_sparse(t_par **p);



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


	if(ft_is_whitespace(argv[*size + *i]))
		p->fusion = 1;
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
	if (ft_is_whitespace(argv[*size + *i]))
		p->fusion = 1;

	return (p);
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
	return(fusion_sparse(p));
}

static t_par	**fusion_sparse(t_par **p)
{
	t_par	**new;
	int		i;
	int		j;

	new = (t_par **) malloc(sizeof(t_par *) * (tparlen(p) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (p[i])
	{
		new[j] = (t_par *) malloc(sizeof(t_par));
		if (!new[j])
			return (NULL);
		if (p[i + 1] && p[i]->fusion == 1 && p[i]->type == 0 && p[i + 1]->type == 0)
		{
			new[j]->str = ft_strjoin(p[i]->str, p[i + 1]->str);
			new[j]->type = 0;
			new[j++]->fusion = p[i + 1]->fusion;
			i++;
		}
		else
		{
			new[j]->str = ft_strdup(p[i]->str);
			new[j]->type = p[i]->type;
			new[j]->fusion = p[i]->fusion;
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_t_par(p);
	return (new);
}

static int	tparlen(t_par **p)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (p[i + 1])
	{
		if (p[i]->fusion == 1 && p[i]->type == 0 && p[i + 1]->type == 0)
			res--;
		res++;
		i++;
	}
	return (res);
}
