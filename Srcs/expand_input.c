/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:57:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/30 21:01:09 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	quotes_word_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (*str == '\'')
		return (simplequote(&i, str) + 1);
	if (*str == '"')
		return (doublequote(&i, str) + 1);
	j = 0;
	return (ft_min(simplequote(&i, str), doublequote(&j, str)));
}

static int	operands_word_len(char *str)
{
	int	first_type;
	int	size;

	if (!str || !*str)
		return (0);
	size = 1;
	first_type = ft_isoperand(str[0]);
	while (str[size] && first_type == ft_isoperand(str[size])
		&& (!first_type || str[0] == str[size]))
		size++;
	return (size);
}

static int	cmd_word_len(char *str)
{
	int	test;
	int	q_word_len;
	int	o_word_len;

	q_word_len = quotes_word_len(str);
	o_word_len = operands_word_len(str);
	test = ft_isoperand(*str) || (*str != '"' && *str != '\'');
	return (q_word_len * !test + ft_min(o_word_len, q_word_len) * test);
}

static char	*expand_word(char **word, t_env *env)
{
	char	*temp;

	if (!word || !*word || !env)
		return (NULL);
	if (!ft_isoperand(*word[0]) && *word[0] != '\'' && ft_strchr(*word, '$'))
	{
		temp = expand_dollars(*word, env);
		if (!temp)
			return (NULL);
		free(*word);
		*word = temp;
	}
	return (*word);
}

char	**expand_line(char *line, t_env *env)
{
	int		i;
	char	**line_split;

	if (!line | !env)
		return (NULL);
	line_split = ft_fsplit(line, cmd_word_len);
	if (!line_split)
		return (NULL);
	i = -1;
	while (line_split[++i])
	{
		if (expand_word(line_split + i, env))
			continue ;
		free_str_tab((void **)line_split);
		return (NULL);
	}
	if (check_line_words((const char **)line_split))
	{
		free_str_tab((void **)line_split);
		line_split = NULL;
	}
	return (line_split);
}
