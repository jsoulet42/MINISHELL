/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_shlvl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:17:42 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/07 14:42:05 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	modif_shlvl(t_env **env)
{
	char	*tmp;
	char	*new_lvl;

	if (!env || !*env)
		return (SH_ERROR);
	tmp = ft_getenv(*env, "SHLVL");
	if (!tmp)
		return (SH_ERROR);
	new_lvl = ft_itoa(ft_atoi(tmp) + 1);
	if (!new_lvl)
		return (SH_ERROR);
	tmp = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	if (!tmp)
		return (SH_ERROR);
	export_var(tmp, env, SH_OVERWRITE);
	free(tmp);
	return (SH_SUCCESS);
}
