/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:38 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/04 12:58:19 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_strccmp(const char *str1, const char *str2, char limit)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && str1[i] != limit && str2[i] != limit)
	{
		if (str1[i] != str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	if (str1[i] && str1[i] != limit)
		return ((unsigned char) str1[i]);
	if (str2[i] && str2[i] != limit)
		return (- (unsigned char) str2[i]);
	return (0);
}

char	*ft_strjoin_plus(char *dest, char *src)
{
	if (!dest || !src)
		return (ft_strdup((char *)((uintptr_t) src * (1 && src)
				+ (uintptr_t) dest * (1 && dest))));
	return (ft_strjoin(dest, src));
}

char	*ft_free_strcat(char **dest, char *src, int start, int end)
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
	int		id[2];
	char	*temp;

	if (!str_tab || !str_tab[0] || !str_tab[1])
		return (str_tab);
	id[0] = 0;
	id[1] = 1;
	while (str_tab[id[0] + 1])
	{
		if (ft_strccmp(str_tab[id[0]], str_tab[id[1]], limit) > 0)
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
	{
		ft_fprintf(2, "NULL\n");
		return ;
	}
	while (*str_tab)
		ft_fprintf(2, "[%s] ", *str_tab++);
	ft_fprintf(2, "\n");
}
