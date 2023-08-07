/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplquote_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:19:14 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 13:19:16 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	simplquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == 39)
			return (i);
		i++;
	}
	return (-1);
}
