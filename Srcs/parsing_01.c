/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:21:56 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/31 19:46:28 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_rinity	**ft_parsing(char *argv)
{
//	int			res;
	char		**line_tab;
	t_rinity	**t;

//	res = count_arg(argv, 0);
//	g_shell_data->par = (t_par **) malloc(sizeof(t_par *) * (res + 1));
//	if (!g_shell_data->par)
//		return (NULL);
	line_tab = expand_line(argv, g_shell_data->env);
	if (!line_tab)
		return (NULL);
//	sparse(g_shell_data->par, cmd_tab);
//	if (check_line(g_shell_data->par))
//		return (NULL);
	t = t_rinity_init(line_tab);
	free_str_tab((void **)line_tab);
	if (!t)
		ft_perror("mishelle", __func__);
	return (t);
}

static char	*unquote_and_merge(char ***line_tab)
{
	int		is_quoted;
	char	*temp;
	char	*res;
	char	**moved_tab;

	if (!line_tab || !*line_tab || !**line_tab)
		return (NULL);
	moved_tab = *line_tab;
	is_quoted = **moved_tab == '"' || **moved_tab == '\'';
	res = ft_substr(*moved_tab, is_quoted,
			ft_strlen(*moved_tab) - 2 * is_quoted);
	if (!res)
		return (NULL);
	moved_tab++;
	while (*moved_tab && !ft_isoperand(**moved_tab)
		&& !ft_strchr(" \t\n\v\f\r", **moved_tab))
	{
		is_quoted = **moved_tab == '"' || **moved_tab == '\'';
		temp = ft_substr(*moved_tab, is_quoted,
				ft_strlen(*moved_tab) - 2 * is_quoted);
		if (!temp)
			return (free(res), NULL);
		if (!ft_free_strcat(&res, temp, 0, ft_strlen(temp)))
			return (safe_free((void **)res), free(temp), NULL);
		free(temp);
		moved_tab++;
	}
	*line_tab = moved_tab;
	return (res);
}

static t_rinity	*t_rinity_init_utils(char **line_tab)
{
	char		*temp;
	t_rinity	*t;

	t = (t_rinity *) ft_calloc(1, sizeof(t_rinity));
	if (!t)
		ft_putstr_fd("malloc error // init_t_rinity\n", 2);
	while (*line_tab && (*line_tab)[0] != '|')
	{
		if (!ft_strncmp(*line_tab, ">", 2) || !ft_strncmp(*line_tab, ">>", 3))
		{
			t->type_out = str_tab_add_neo(t->type_out, *line_tab++);
			while (ft_strchr(" \t\n\v\f\r", **line_tab))
				line_tab++;
			temp = unquote_and_merge(&line_tab);
			if (!temp)
				return (NULL);
			t->file_out = str_tab_add_neo(t->file_out, temp);
		}
		else if (!ft_strncmp(*line_tab, "<", 2) || !ft_strncmp(*line_tab, "<<", 3))
		{
			t->type_in = str_tab_add_neo(t->type_in, *line_tab++);
			while (ft_strchr(" \t\n\v\f\r", **line_tab))
				line_tab++;
			temp = unquote_and_merge(&line_tab);
			if (!temp)
				return (NULL);
			t->file_in = str_tab_add_neo(t->file_in, temp);
		}
		else if ((*line_tab)[0] != ' ')
		{
			temp = unquote_and_merge(&line_tab);
			if (!temp)
				return (NULL);
			t->cmd = str_tab_add_neo(t->cmd, temp);
		}
		else
			line_tab++;
/*
		t->type_in = create_type_in(line_tab);
		t->type_out = create_type_out(line_tab);
		t->file_in = create_file_in(line_tab);
		t->file_out = create_file_out(line_tab);
		t->kafka = create_kafka(line_tab);
		line_tab++;
*/	}
//	print_str_tab((char*[]){"hey", "qwdqwd", NULL});
	return (t);
}

t_rinity	**t_rinity_init(char **line_tab)
{
	int			cmds_count;
	t_rinity	**t;
	t_rinity	**temp;

	cmds_count = real_cmd(line_tab);
	t = (t_rinity **) ft_calloc(sizeof(t_rinity *), cmds_count + 1);
	if (!t)
		return (NULL);
	temp = t;
	while (cmds_count--)
	{
		*temp = t_rinity_init_utils(line_tab);
		if (!*temp)
			return(free_trinity(t), NULL);
		line_tab += next_pipe(line_tab) + 1;
		temp++;
	}
	return (t);
}

void	ft_supprchar(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(*str, 0, i);
	tmp2 = ft_substr(*str, i + 1, ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
