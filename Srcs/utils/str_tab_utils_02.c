/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:36:22 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 14:50:32 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_free_strcat(char **dest, char *src)
{
	char	*temp;

	temp = ft_strjoin_plus(*dest, src);
	safe_free((void **) dest);
	if (!temp)
		return (NULL);
	*dest = temp;
	return (*dest);
}

char	*ft_strjoin_plus(char *dest, char *src)
{
	if (!dest || !src)
		return (ft_strdup((char *)((uintptr_t) src * (1 && src)
				+ (uintptr_t) dest * (1 && dest))));
	return (ft_strjoin(dest, src));
}

char	*join_str_tab(const char **str_tab)
{
	char	*res;
	char	*temp;
	char	**temp_tab;

	if (!str_tab || !*str_tab)
		return (NULL);
	if (!*(str_tab + 1))
		return (ft_strdup(*str_tab));
	res = NULL;
	temp_tab = (char **)str_tab;
	while (*temp_tab)
	{
		temp = ft_strjoin_plus(res, *temp_tab);
		safe_free((void **)&res);
		if (!temp)
			return (NULL);
		res = temp;
		temp_tab++;
	}
	return (res);
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
