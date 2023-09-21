/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:38 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/21 07:00:38 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	str_tab_len(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	print_str_tab(int fd, char **str_tab)
{
	int	len;

	if (!str_tab)
		return (ft_fprintf(fd, "NULL\n"));
	len = 0;
	while (*str_tab)
		len += ft_fprintf(fd, "[%s] ", *str_tab++);
	len += ft_fprintf(fd, "\n");
	return (len);
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
