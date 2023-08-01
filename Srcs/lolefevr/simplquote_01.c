/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplquote_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:56:20 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/28 16:33:54 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int simplquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == 39)
			return (i);
		i++;
	}
	//error
	return (-1);
}
