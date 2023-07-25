/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lentab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:28:48 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/17 15:32:23 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	lentab(char **tableau)
{
	int	i;

	i = -1;
	while(tableau[++i])
		i = i;
	return (i);
}
