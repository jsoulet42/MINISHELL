/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:53 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 12:41:46 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	doublequote(int *i, char *str)
{
	int	start;

	if (!i || !str)
		return (0);
	start = *i;
	(*i)++;
	while (str[*(i)] && str[*(i)] != 34)
		(*i)++;
	return (*i - start);
}

int	simplequote(int *i, char *str)
{
	int	start;

	if (!i || !str)
		return (0);
	start = *i;
	(*i)++;
	while (str[*(i)] && str[*(i)] != 39)
		(*i)++;
	return (*i - start);
}
