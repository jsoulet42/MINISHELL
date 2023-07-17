/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:10:11 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/16 23:40:55 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/hnogared.h"

int	ft_export(char **argv, t_env *env)
{
	int		i;
	int		len;
	char	*var_name;
	t_env	*var;

	if (!argv || !*argv)
		return (SH_ERROR);
	if (!argv[1])
		return (print_env(env, SH_ORDERED), SH_SUCCESS);
	i = 0;
	while (argv[++i])
	{
		var_name = ft_substr(argv[i], 0, ft_strchr(argv[i], '=') - argv[i]);
		var = get_env_var(env, var_name);
		free(var_name);
		if (!var)
		{
			var = new_env_var(argv[i], NULL);
			if (!var)
				return (SH_ERROR);
			env_add_back(&env, var);
			continue ;
		}
		len = ft_strchr(argv[i], '=') - argv[i];
		update_env_var(var, argv[i] + len, SH_OVERWRITE);
	}
	return (SH_SUCCESS);
}
