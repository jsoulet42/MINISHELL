/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_07.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:29:53 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/31 12:45:24 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		if (!new[i])
			return (NULL);
		i++;
	}
	free(str);
	new[i] = add;
	new[i + 1] = NULL;
	return (new);
}

char	**new_neo(char *add)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * 2);
	if (!new)
		return (NULL);
	new[0] = add;
	if (!new[0])
		return (NULL);
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