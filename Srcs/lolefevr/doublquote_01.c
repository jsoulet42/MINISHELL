/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublquote_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:56:24 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/12 11:09:57 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
