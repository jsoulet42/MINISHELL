/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:57:49 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/28 15:26:51 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_quotes(char *str)
{
	char	quote;

	if (!str)
		return (1);
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && (quote == 0 || quote == *str))
			quote = (quote == 0) * *str;
		str++;
	}
	return (quote != 0);
}

static int	get_word_len(char *str)
{
	if (*str == '\'' || *str == '"')
		return ((uintptr_t)(ft_strchrnul(str + 1, *str) - str + 1));
	return (ft_min((uintptr_t)(ft_strchrnul(str, '\'') - str),
		(uintptr_t)(ft_strchrnul(str, '"') - str)));
}

static char	**split_quotes_words(char *str, int mode, t_env *env)
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
		if ((mode == SH_UNBOUND || word[0] != '\'') && ft_strchr(word, '$'))
		{
			res = str_tab_add_neo(res, expand_dollars(word, env));
			free(word);
		}
		else
			res = str_tab_add_neo(res, word);
	}
	return (res);
}

char	*expand_input(char *cmd, int mode, t_env *env)
{
	char	*res;
	char	**quotes_split;

	if (!cmd | !env)
		return (NULL);
	quotes_split = split_quotes_words(cmd, mode, env);
	if (!quotes_split)
		return (NULL);
	res = join_str_tab((const char **)quotes_split);
	free_str_tab((void **)quotes_split);
	return (res);
}
