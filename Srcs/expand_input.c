/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:57:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/29 15:57:07 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	get_word_len(char *str)
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

static char	**split_quotes_words(char *str, t_env *env)
{
	int		len;
	char	*word;
	char	**res;

	if (!str || !env)
		return (NULL);
	res = NULL;
	while (*str)
	{
		len = get_word_len(str);
		word = ft_substr(str, 0, len);
		if (!word)
			return (free_str_tab((void **)res), NULL);
		str += len;
		if (word[0] != '\'' && ft_strchr(word, '$'))
		{
			res = str_tab_add_neo(res, expand_dollars(word, env));
			free(word);
		}
		else
			res = str_tab_add_neo(res, word);
	}
	return (res);
}

char	*expand_input(char *cmd, t_env *env)
{
	char	*res;
	char	**quotes_split;

	if (!cmd | !env)
		return (NULL);
	quotes_split = split_quotes_words(cmd, env);
	if (!quotes_split)
		return (NULL);
	res = join_str_tab((const char **)quotes_split);
	free_str_tab((void **)quotes_split);
	return (res);
}
