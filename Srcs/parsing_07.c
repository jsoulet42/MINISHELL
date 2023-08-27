/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_07.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:25:02 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/27 22:42:24 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	free_t_par(t_par **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]->str);
		free(p[i]);
		i++;
	}
	free(p);
	p = NULL;
}

char	**str_tab_add_neo(char **str, char *add)
{
	int		i;
	char	**new;

	if (!str)
		return (new_neo(add));
	i = strstr_len(str);
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

int	strstr_len(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_addchar(char **str, int i, char *c)
{
	char	*tmp1;
	char	*tmp2;

	tmp2 = ft_substr(*str, 0, i + 1);
	tmp1 = ft_strjoin_plus(tmp2, c);
	free(tmp2);
	tmp2 = ft_substr(*str, i + ft_strlen(c), ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
