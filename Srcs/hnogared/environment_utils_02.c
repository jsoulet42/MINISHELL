/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:26:42 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 02:24:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_env	*get_env_var(t_env *env_list, char *var_name)
{
	int	name_len;

	if (!env_list || !var_name)
		return (NULL);
	name_len = ft_strlen(var_name);
	while (env_list && ft_strncmp(env_list->name, var_name, name_len))
		env_list = env_list->next;
	return (env_list);
}

static int	update_env_value(t_env *env_var, char *value, int mode)
{
	char	*temp;

	if (mode == SH_OVERWRITE)
	{
		safe_free((void **) &env_var->value);
		if (value)
			env_var->value = ft_strdup(value);
		else
			env_var->value = ft_strdup("");
	}
	else if (value)
	{
		temp = env_var->value;
		env_var->value = ft_strjoin(temp, value);
		free(temp);
	}
	if (!env_var->value)
		return (1);
	return (0);
}

t_env	*update_env_var(t_env *env_var, char *value, int mode)
{
	char	*temp;

	if (!env_var)
		return (NULL);
	if (!value && mode == SH_CONCAT)
		return (env_var);
	if (update_env_value(env_var, value, mode))
		return (NULL);
	safe_free((void **) &env_var->display);
	temp = ft_strjoin(env_var->name, "=");
	if (!temp)
		return (NULL);
	env_var->display = ft_strjoin(temp, env_var->value);
	free(temp);
	if (!env_var->display)
		return (NULL);
	return (env_var); 
}
