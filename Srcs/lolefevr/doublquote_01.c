/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublquote_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:56:24 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/12 19:10:36 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int doublquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((int)str[i] == 34)
			return (i);
		i++;
	}
	//error !!
	return (-1);
}
