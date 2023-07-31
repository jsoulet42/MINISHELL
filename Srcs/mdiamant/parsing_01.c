/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:09:47 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/31 13:28:43 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_rinity	**ft_parsing(char *argv)
{
	int			res;
	char		*line;
	t_rinity	**t;

	line = ft_strtrim(argv, " ");
	res = count_arg(line, 0);
	g_shell_data->par = (t_par **) malloc(sizeof(t_par *) * (res + 1));
	if (!g_shell_data->par)
		ft_fprintf(2, "malloc error // ft_parsing\n");
	fusion_arg(&line);
	ft_fprintf(2, "line : %s\n", line);
	sparse(g_shell_data->par, line);
	check_line(g_shell_data->par);
	free(line);
	t = t_rinity_init(g_shell_data->par);
	print_t_rinity(t);
	return (t);
}

static int	sparse_utils(char *argv, t_par **p, int *i, int *j)
{
	int	size;

	if (argv[*i] == '\'')
		p[*j]->quote_type = 1;
	size = is_quote(argv + *i);
	if (size == 0)
		p[*j]->str = ft_strdup("\0");
	else
		p[*j]->str = ft_substr(argv, *i + 1, size);
	p[*j++]->type = 0;
	i += 2;
	return (size);
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
		p[j] = (t_par *) malloc(sizeof(t_par));
		if (!p[j])
			ft_fprintf(2, "malloc error // sparse\n");
		p[j]->quote_type = 2;
		if (is_quote(argv + i) != -1)
			size = sparse_utils(argv, p, &i, &j);
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

static t_rinity	*t_rinity_init_utils(t_par **p, int len)
{
	t_rinity	*t;

	t = (t_rinity *) malloc(sizeof(t_rinity));
	if (!t)
		ft_putstr_fd("malloc error // init_t_rinity\n", 2);
	t->command = NULL;
	t->type_in = NULL;
	t->type_out = NULL;
	t->file_in = NULL;
	t->file_out = NULL;
	t->kafka = NULL;
	t->command = create_commande(p, len);
	t->type_in = create_type_in(p, len);
	t->type_out = create_type_out(p, len);
	t->file_in = create_file_in(p, len);
	t->file_out = create_file_out(p, len);
	t->kafka = create_kafka(p, len);
	return (t);
}

t_rinity	**t_rinity_init(t_par **p)
{
	t_rinity	**t;
	int			cmd;
	int			i;
	int			len;

	i = 0;
	len = 0;
	cmd = real_cmd(p);
	t = (t_rinity **) malloc(sizeof(t_rinity *) * (cmd + 1));
	if (!t)
		ft_putstr_fd("malloc error1 // t_rinity_init\n", 2);
	while (i < cmd && p[len])
	{
		t[i] = ft_calloc(sizeof(t_rinity), 1);
		if (!t[i])
			ft_putstr_fd("malloc error2 // t_rinity_init\n", 2);
		t[i] = t_rinity_init_utils(p, len);
		len = next_pipe(p, i);
		i++;
	}
	t[cmd] = NULL;
	return (t);
}
