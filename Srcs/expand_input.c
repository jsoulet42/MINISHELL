/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:57:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/30 17:57:52 by hnogared         ###   ########.fr       */
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

static int	ft_isoperand(char c)
{
	char	to_find[2];

	to_find[0] = c;
	to_find[1] = 0;
	return (c != ':' && c != '\'' && c != '"'
		&& !ft_strnstr(OPERANDS, to_find, ft_strlen(OPERANDS)));
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
		&& (first_type || str[0] == str[size]))
		size++;
	return (size);
}

static char	*expand_word(char **word, t_env *env)
{
	char	*temp;
	char	**operands_split;

	if (word && *word && *word[0] != '\'' && ft_strchr(*word, '$'))
	{
		temp = expand_dollars(*word, env);
		if (!temp)
			return (NULL);
		free(*word);
		*word = temp;
	}
	if (word && *word && *word[0] != '\'' && *word[0] != '"')
	{
		operands_split = ft_fsplit(*word, operands_word_len);
		if (!operands_split)
			return (NULL);
		temp = join_str_tab_mono((const char **)operands_split);
		free_str_tab((void **)operands_split);
		if (!temp)
			return (NULL);
		free(*word);
		*word = temp;
	}
	return (*word);
}

static int	quotes_word_len2(char *str)
{
	int	test;

	test = ft_isoperand(*str) || *str != '"' || *str != '\'';
	ft_printf("%d : %c : is_ope(%d)\n", test, *str, ft_isoperand(*str));
	return (quotes_word_len(str) * !test + operands_word_len(str) * test);
}

char	*expand_input(char *cmd, t_env *env)
{
	int		i;
	char	*res;
	char	**quotes_split;

	if (!cmd | !env)
		return (NULL);
	quotes_split = ft_fsplit(cmd, quotes_word_len);
	if (!quotes_split)
		return (NULL);
	i = 0;
	while (quotes_split[i])
	{
		if (!expand_word(&quotes_split[i], env))
			return (free_str_tab((void **)quotes_split), NULL);
		i++;
	}
	res = join_str_tab((const char **)quotes_split);
	free_str_tab((void **)quotes_split);
	quotes_split = ft_fsplit(cmd, quotes_word_len2);
	if (!quotes_split)
		return (NULL);
	print_str_tab(quotes_split);
	free_str_tab((void **)quotes_split);
	return (res);
}
