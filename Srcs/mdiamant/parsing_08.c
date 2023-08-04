#include "../../Includes/minishell.h"

t_par	*sparse_utils_01(char *argv, int *i, int *size)
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
	if (ft_is_whitespace(argv[*size + *i + 2]))
		p->fusion = 1;
	*i += 2;
	return (p);
}

t_par	*sparse_utils_02(char *argv, int *i, int *size)
{
	t_par	*p;

	p = (t_par *) malloc(sizeof(t_par));
	if (!p)
		return (NULL);
	p->fusion = 0;
	*size = calc_size_type(argv + *i);
	p->type = calc_type(argv + *i);
	p->str = ft_substr(argv, *i, *size);
	if (ft_is_whitespace(argv[*size + *i]) && argv[*size + *i + 1] != '\0')
		p->fusion = 1;
	return (p);
}

char	*fusion_sparse_utils(t_par **p, int *i)
{
	char	*dest;
	char	*tmp;

	dest = ft_strdup(p[*i]->str);
	if (!dest)
		return (NULL);
	while (p[*i] && p[*i]->fusion == 1 && p[*i + 1]->type == 0)
	{
		if (p[*i + 1] && p[*i + 1]->type == 0)
			tmp = ft_strjoin_plus(dest, p[*i + 1]->str);
		if (dest)
			free(dest);
		dest = ft_strdup(tmp);
		if (!dest)
			return (NULL);
		if (tmp)
			free(tmp);
		*i += 1;
	}
	return (dest);
}

t_par	**fusion_sparse(t_par **p)
{
	t_par	**new;
	int		i;
	int		j;

	new = t_par_init(tparlen(p));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (p[i])
	{
		if (p[i + 1] && p[i]->fusion == 1 && p[i]->type == 0
			&& p[i + 1]->type == 0)
			new[j++]->str = fusion_sparse_utils(p, &i);
		else
		{
			new[j]->str = ft_strdup(p[i]->str);
			new[j++]->type = p[i]->type;
		}
		ft_fprintf(2, "new[%d]->str = %s\n", j - 1, new[j - 1]->str);
		i++;
	}
	free_t_par(p);
	return (new);
}

t_par	**t_par_init(int len)
{
	t_par	**p;

	p = (t_par **) malloc(sizeof(t_par *) * (len + 1));
	if (!p)
		return (NULL);
	p[len--] = NULL;
	while (len >= 0)
	{
		p[len] = (t_par *) malloc(sizeof(t_par));
		if (!p[len])
			return (NULL);
		p[len]->str = NULL;
		p[len]->type = 0;
		p[len]->fusion = 0;
		len--;
	}
	return (p);
}
