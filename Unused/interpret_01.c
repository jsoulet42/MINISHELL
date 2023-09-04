/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:31:39 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/04 12:32:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	check_line(t_par **par)
{
	int	i;

	i = 0;
	while (par[i])
	{
		if (par[i]->type != 0 && par[i + 1] && par[i + 1]->type != 0)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i + 1]->str));
		}
		if (par[i]->type != 0 && par[i + 1] == NULL)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i]->str));
		}
		i++;
	}
	return (0);
}
