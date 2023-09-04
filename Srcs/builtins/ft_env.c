/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:09:46 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 15:44:37 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_env(int argc, char **argv, t_env **env)
{
	t_env	*temp;

	if (!env)
		return (SH_ERROR);
	if (argc > 1)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: env: too many arguments\n");
		return (SH_ERROR);
	}
	(void)argv;
	temp = *env;
	while (temp)
	{
		if (temp->value)
			printf("%s\n", temp->display);
		temp = temp->next;
	}
	return (SH_SUCCESS);
}
