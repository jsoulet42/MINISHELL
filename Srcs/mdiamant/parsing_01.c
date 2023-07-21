/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:09:47 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/20 19:59:19 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../Includes/minishell.h"

t_rinity	**ft_parsing(char *argv)
{
	int		res;
	char	*line;
	t_rinity **t;

	line = ft_strtrim(argv, " ");
	res = count_arg(line);
	g_shell_data->par = (t_par **) malloc(sizeof(t_par *) * (res + 1));
	if (!g_shell_data->par)
		ft_fprintf(2, "malloc error // ft_parsing\n");
	sparse(g_shell_data->par, line);
	command_nb(g_shell_data->par);
	check_line(g_shell_data->par);
	free(line);
	t = t_rinity_init(g_shell_data->par);
	print_t_rinity(t);
	return (t);
}

void	command_nb(t_par **p)
{
	int	i;
	int	j;

	i = 1;
	p[0]->command_elem_id = 1;
	while (p[i])
	{
		p[i]->command_elem_id = 0;
		j = is_operand(p[i]->str);
		if (j != 0 && p[i + 1] && p[i + 2])
		{
			p[i + 1]->command_elem_id = 1;
			i += j;
		}
		i++;
	}
}

void	print_t_par(t_par **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		ft_fprintf(2, "p[%d] : str : '%s' // type : %d // quote_type : %d // command_elem_id : %d\n", i, p[i]->str, p[i]->type, p[i]->quote_type, p[i]->command_elem_id);
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
		p[j] = (t_par *) malloc(sizeof(t_par));
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
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
		i++;
	return (i);
}

t_rinity **t_rinity_init(t_par **p)
{
	t_rinity **t;
	int	cmd;
	int	i;
	int	len;

	i = 0;
	len = 0;
	cmd = real_cmd(p);
	t = (t_rinity**)malloc(sizeof(t_rinity *) * (cmd + 1));
	if (!t)
	{
		ft_putstr_fd("malloc error1 // t_rinity_init\n", 2); //ajouter fonction exit
		exit(1);
	}
	while (i < cmd)
	{
		t[i] = ft_calloc(sizeof(t_rinity), 1);
		if (!t[i])
		{
			ft_putstr_fd("malloc error2 // t_rinity_init\n", 2); //ajouter fonction exit
			exit(1);
		}
		t[i]->command = NULL;
		t[i]->type_in = NULL;
		t[i]->type_out = NULL;
		t[i]->file_in = NULL;
		t[i]->file_out = NULL;
		t[i]->kafka = NULL;
		t[i]->command = create_commande(p);
		len = next_pipe(p, i);
		t[i]->type_in = create_type_in(p, len);
		t[i]->type_out = create_type_out(p, len);
		t[i]->file_in = create_file_in(p, len);
		t[i]->file_out = create_file_out(p, len);
		t[i]->kafka = create_kafka(p, len);
		len = next_pipe(p, i);
		i++;
	}
	t[cmd] = NULL;
	return (t);
}

int	next_pipe(t_par **p, int i)
{
	int	j;
	int	res;

	j = 0;
	res = 0;
	while (p[j])
	{
		if (p[j]->type == 1)
			res++;
		if (res == i)
			break ;
		j++;
	}
	return (++j);
}

char	**create_type_out(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 3 || p[i]->type == 4)
			new = str_tab_add_neo(new, p[i]->str);
		i++;
	}

	return(new);
}
char	**create_type_in(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 2 || p[i]->type == 5)
			new = str_tab_add_neo(new, p[i]->str);
		i++;
	}
	return(new);
}

char	**create_file_out(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 4)
			{
				// new = str_tab_add_neo(new, ft_heredoc(p[i + 1]));
				i++;
			}
		if (p[i]->type == 3)
		{
			new = str_tab_add_neo(new, p[i + 1]->str);
			i++;
		}
		i++;
	}
	return(new);
}
char	**create_file_in(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 2 || p[i]->type == 5)
				new = str_tab_add_neo(new, p[i + 1]->str);
		i++;
	}
	return(new);
}
char	**create_kafka(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type >= 2 && p[i]->type <= 5)
				new = str_tab_add_neo(new, p[i]->str);
		i++;
	}
	return(new);
}
char	**str_tab_add_neo(char **str, char *add)
{
	int		i;
	char	**new;

	if (!str)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(add);
		new[1] = NULL;
		return (new);
	}
	i = strstr_len(str);
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = ft_strdup(str[i]);
		free(str[i]);
		i++;
	}
	new[i] = ft_strdup(add);
	new[i + 1] = NULL;
	return (new);
}

int	strstr_len(char **str)
{
	int	i;

	i = 0;
	if (str)
		return (0);
	while (str[i])
		i++;
	return(i);
}

void	print_t_rinity(t_rinity **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		ft_fprintf(2, "la commande est : ");
		print_str_tab(t[i]->command);

		ft_fprintf(2, "type_in : ");
		print_str_tab(t[i]->type_in);
		ft_fprintf(2, "type_out : ");
		print_str_tab(t[i]->type_out);
		ft_fprintf(2, "file_in : ");
		print_str_tab(t[i]->file_in);
		ft_fprintf(2, "file_out : ");
		print_str_tab(t[i]->file_out);
		ft_fprintf(2, "kafka : ");
		print_str_tab(t[i]->kafka);
		i++;
	}
}

int	real_cmd(t_par **par)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (par[i])
	{
		if (par[i]->type == 1)
			j++;
		i++;
	}
	return (j);
}
