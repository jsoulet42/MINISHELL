/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:21:56 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 15:31:37 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to split and store a string inside an array of t_rinity structures
 * Each structure stores a parsed command with its arguments and redirections
 *
 * @param char *argv	-> pointer to the input string
 * @return t_rinity **	-> pointer to the parsed commands structures' tab
 */
t_rinity	**ft_parsing(char *line)
{
	char		**line_tab;
	t_rinity	**t;

	if (!line || check_starterrors(line) != SH_SUCCESS)
	{
		g_shell_data.exit_code = 1;
		return (NULL);
	}
	line_tab = expand_line(line, g_shell_data.env);
	if (!line_tab)
		return (NULL);
	if (check_line_words((const char **)line_tab))
	{
		free_str_tab((void **)line_tab);
		return (NULL);
	}
	t = t_rinity_init(line_tab);
	free_str_tab((void **)line_tab);
	return (t);
}

/* Function to unquote and join successive strings of a strings array which
 * don't start with a whitespace character or a shell operand
 * /!\ The pointer *line_tab is incremented until 
 *
 * @param
 */
static char	*unquote_and_join(char ***line_tab)
{
	int		quote;
	char	*temp;
	char	*res;
	char	**moved_tab;

	if (!line_tab || !*line_tab || !**line_tab)
		return (NULL);
	moved_tab = *line_tab;
	quote = **moved_tab == '"' || **moved_tab == '\'';
	res = ft_substr(*moved_tab, quote, ft_strlen(*moved_tab) - 2 * quote);
	if (!res)
		return (NULL);
	moved_tab++;
	while (*moved_tab && !ft_isoperand(**moved_tab)
		&& !ft_strchr(" \t\n\v\f\r", **moved_tab))
	{
		quote = **moved_tab == '"' || **moved_tab == '\'';
		temp = ft_substr(*moved_tab, quote, ft_strlen(*moved_tab) - 2 * quote);
		if (!ft_free_strcat(&res, temp))
			return (safe_free((void **)res), safe_free((void **)temp), NULL);
		free(temp);
		moved_tab++;
	}
	*line_tab = moved_tab;
	return (res);
}

static int	store_redirection(t_rinity **t, char ***line_tab)
{
	char	*redir;
	char	*temp;
	char	**moved_tab;

	if (!t || !*t || !line_tab || !*line_tab || !**line_tab)
		return (SH_ERROR);
	moved_tab = *line_tab;
	redir = *moved_tab++;
	while (*moved_tab && ft_strchr(" \t\n\v\f\r", **moved_tab))
		moved_tab++;
	temp = unquote_and_join(&moved_tab);
	if (!temp)
		return (SH_ERROR);
	if (*redir == '>')
	{
		(*t)->type_out = str_tab_add_neo((*t)->type_out, ft_strdup(redir));
		(*t)->file_out = str_tab_add_neo((*t)->file_out, temp);
	}
	if (*redir == '<')
	{
		(*t)->type_in = str_tab_add_neo((*t)->type_in, ft_strdup(redir));
		(*t)->file_in = str_tab_add_neo((*t)->file_in, temp);
	}
	*line_tab = moved_tab;
	return (SH_SUCCESS);
}

static t_rinity	*t_rinity_init_utils(char **line_tab)
{
	char		*temp;
	t_rinity	*t;

	if (!line_tab || !*line_tab)
		return (NULL);
	t = (t_rinity *) ft_calloc(1, sizeof(t_rinity));
	if (!t)
		return (NULL);
	while (*line_tab && **line_tab != '|')
	{
		if ((**line_tab == '<' || **line_tab == '>')
			&& store_redirection(&t, &line_tab) != SH_SUCCESS)
			return (free_trinity_struct(t), NULL);
		else if (*line_tab && !ft_strchr(" \t\n\v\f\r", **line_tab))
		{
			temp = unquote_and_join(&line_tab);
			if (!temp)
				return (free_trinity_struct(t), NULL);
			t->cmd = str_tab_add_neo(t->cmd, temp);
		}
		else if (*line_tab)
			line_tab++;
	}
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
			return (free_trinity_tab(&t), NULL);
		line_tab += next_pipe(line_tab) + 1;
		temp++;
	}
	return (t);
}
