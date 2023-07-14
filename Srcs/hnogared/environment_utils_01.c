/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:08:06 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 02:41:49 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_env	*new_env_var(char *var_str, void *next)
{
	int		len;
	int		var_str_len;
	t_env	*new;

	if (!var_str)
		return (NULL);
	new = (t_env *) ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	len = ft_strchr(var_str, '=') - var_str;
	new->name = ft_substr(var_str, 0, len);
	if (!new->name)
		return (free(new), NULL);
	var_str_len = ft_strlen(var_str);
	new->value = ft_substr(var_str, len + 1, var_str_len - len);
	if (!new->value)
		return (del_env_var(new, NULL, NULL), NULL);
	new->display = ft_substr(var_str, 0, var_str_len);
	if (!new->display)
		return (del_env_var(new, NULL, NULL), NULL);
	new->next = next;
	return (new);
}

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

void	print_env(t_env *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		printf("%s\n", env_list->display);
		env_list = env_list->next;
	}
}

void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var)
{
	if (!env_var)
		return ;
	if (prev_var)
		prev_var->next = next_var;
	safe_free((void **) &env_var->name);
	safe_free((void **) &env_var->value);
	safe_free((void **) &env_var->display);
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
