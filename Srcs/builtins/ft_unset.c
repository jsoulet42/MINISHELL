/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:21:45 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/18 18:26:55 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../Includes/minishell.h"

int	ft_unset(char **argv, t_env *env)
{
	t_env	*var;

	if (!argv || !*argv)
		return (SH_ERROR);
	if (!env)
		return (SH_SUCCESS);
	while (*++argv)
	{
		var = get_env_var(env, *argv);
		if (var)
			del_env_var(var, var->prev, var->next);
	}
	return (SH_SUCCESS);
}
