/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:08:06 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/13 18:31:15 by dw dqw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_env	*env_add_back(t_env **env_list, t_env *new)
{
	t_env	*temp;

	if (!env_list)
		return (NULL);
	temp = *env_list;
	while (temp && temp->next)
		temp = temp->next;
	if (temp)
		temp->next = new;
	else
		*env_list = new;
	return (*env_list);
}

t_env	*new_env_var(char *var_str, void *next)
{
	int		len;
	t_env	*new;

	if (!var_str)
		return (NULL);
	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	len = ft_strchr(var_str, '=') - var_str;
	new->var_name = strndup(var_str, len);
	if (!new->var_name)
	{
		free(new);
		return (NULL);
	}
	new->var_val = strndup(var_str + len + 1, ft_strlen(var_str) - len);
	new->var_display = var_str;
	new->next = next;
	return (new);
}

void	print_env(t_env *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		printf("%s\n", env_list->var_display);
		env_list = env_list->next;
	}
}

void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var)
{
	if (!env_var)
		return ;
	if (prev_var)
		prev_var->next = next_var;
	if (env_var->var_name)
		free(env_var->var_name);
	if (env_var->var_val)
		free(env_var->var_val);
	free(env_var);
	env_var = NULL;
}

void	free_env(t_env **env_list)
{
	t_env	*next;

	if (!env_list || !*env_list)
		return ;
	while (*env_list)
	{
		next = (*env_list)->next;
		del_env_var(*env_list, NULL, NULL);
		*env_list = next;
	}
	env_list = NULL;
}
