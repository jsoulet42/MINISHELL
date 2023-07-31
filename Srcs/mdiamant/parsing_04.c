/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:17:12 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/31 12:18:41 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	**create_type_out(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 3 || p[i]->type == 4)
			new = str_tab_add_neo(new, p[i]->str);
		i++;
	}
	return (new);
}

char	**create_type_in(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 2 || p[i]->type == 5)
			new = str_tab_add_neo(new, p[i]->str);
		i++;
	}
	return (new);
}

char	**create_file_out(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 4)
		{
			new = str_tab_add_neo(new, p[i + 1]->str);
			i++;
		}
		if (p[i]->type == 3)
		{
			new = str_tab_add_neo(new, p[i + 1]->str);
			i++;
		}
		i++;
	}
	return (new);
}

char	**create_file_in(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type == 2 || p[i]->type == 5)
			new = str_tab_add_neo(new, p[i + 1]->str);
		i++;
	}
	return (new);
}

char	**create_kafka(t_par **p, int i)
{
	char	**new;

	new = NULL;
	while (p[i] && p[i]->type != 1)
	{
		if (p[i]->type >= 2 && p[i]->type <= 5)
			new = str_tab_add_neo(new, p[i]->str);
		i++;
	}
	return (new);
}
