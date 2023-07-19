/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:47:41 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/19 04:11:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_strjoin_plus(char *dest, char *src)
{
	if (!dest && !src)
		return (NULL);
//	if (!dest || !src)
//	{
//		return (ft_strdup((char *)((uintptr_t) &src * (1 && src)
//				+ (uintptr_t) &dest * (1 && dest))));
//	}
	if (!dest)
		return (ft_strdup(src));
	if (!src)
		return (ft_strdup(dest));
	return (ft_strjoin(dest, src));
}

char	*ft_concat(char **dest, char *src, int start, int end)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(src, start, end - start);
	if (!temp)
		return (NULL);
	temp2 = ft_strjoin_plus(*dest, temp);
	free(temp);
	safe_free((void **) dest);
	if (!temp2)
		return (NULL);
	*dest = temp2;
	return (*dest);
}

char	**order_str_tab(char **str_tab, char limit)
{
	int		len;
	int		id[2];
	char	*temp;

	if (!str_tab || !str_tab[0] || !str_tab[1])
		return (str_tab);
	id[0] = 0;
	id[1] = 1;
	while (str_tab[id[0] + 1])
	{
		len = SH_MIN(ft_strchr(str_tab[id[0]], limit) - str_tab[id[0]],
				ft_strchr(str_tab[id[1]], limit) - str_tab[id[1]]) + 1;
		if (ft_strncmp(str_tab[id[0]], str_tab[id[1]], len) > 0)
		{
			temp = str_tab[id[0]];
			str_tab[id[0]] = str_tab[id[1]];
			str_tab[id[1]] = temp;
		}
		id[1]++;
		if (str_tab[id[1]])
			continue ;
		id[0]++;
		id[1] = id[0] + 1;
	}
	return (str_tab);
}

void	print_str_tab(char **str_tab)
{
	if (!str_tab)
		return ;
	while (*str_tab)
		printf("[%s]\n", *str_tab++);
}
