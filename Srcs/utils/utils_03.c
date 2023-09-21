/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:22:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 05:30:18 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_min(int a, int b)
{
	return ((a <= b) * a + (a > b) * b);
}

int	ft_isoperand(char c)
{
	char	to_find[2];

	to_find[0] = c;
	to_find[1] = 0;
	return (c != ':'
		&& ft_strnstr(OPERANDS, to_find, ft_strlen(OPERANDS)));
}

char	**ft_fsplit(char *str, int (*word_len_counter)(char *))
{
	int		word_len;
	char	*word;
	char	**res;

	if (!str || !word_len_counter)
		return (NULL);
	res = NULL;
	while (*str)
	{
		word_len = word_len_counter(str);
		if (word_len < 1)
			return (free_str_tab((void **)res), NULL);
		word = ft_substr(str, 0, word_len);
		if (!word)
			return (free_str_tab((void **)res), NULL);
		str += word_len;
		res = str_tab_add_neo(res, word);
	}
	return (res);
}

char	**new_neo(char *add)
{
	char	**new;

	if (!add)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * 2);
	if (!new)
		return (NULL);
	new[0] = add;
	new[1] = NULL;
	return (new);
}

char	**str_tab_add_neo(char **str, char *add)
{
	int		i;
	char	**new;

	if (!str)
		return (new_neo(add));
	i = str_tab_len(str);
	new = (char **)ft_calloc(sizeof(char *), i + 2);
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	free(str);
	new[i] = add;
	new[i + 1] = NULL;
	return (new);
}
