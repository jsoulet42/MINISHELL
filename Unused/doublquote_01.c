/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublquote_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:17:08 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 17:39:48 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	doublquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == 34)
			return (i);
		i++;
	}
	return (-1);
}
