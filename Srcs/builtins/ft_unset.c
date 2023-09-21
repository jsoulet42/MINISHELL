/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:11:51 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 15:32:06 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to delete a variable from its shell environment
 *
 * @param char **argv	-> pointer to the arguments array
 * @param t_env *env	-> pointer to the shell environment to modify
 * @return int			-> function exit code
 */
int	ft_unset(char **argv, t_env **env)
{
	t_env	*var;

	if (!argv || !*argv)
		return (SH_ERROR);
	if (!*env)
		return (SH_SUCCESS);
	while (*++argv)
	{
		var = get_env_var(*env, *argv);
		if (var)
			del_env_var(var, var->prev, var->next);
	}
	return (SH_SUCCESS);
}
