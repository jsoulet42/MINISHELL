/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:13:50 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 05:49:05 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to allocate a shell environment variable with a given value
 *
 * @param char *var_str	-> pointer to the name and value of the variable
 * @param void *next	-> pointer to the following environment variable
 * @return t_env *		-> pointer to the newly allocated variable structure
 */
t_env	*new_env_var(char *var_str, void *prev, void *next)
{
	int		len[2];
	t_env	*new;

	if (!var_str)
		return (NULL);
	new = (t_env *) ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = next;
	new->prev = prev;
	len[1] = ft_strlen(var_str);
	len[0] = len[1];
	if (ft_strchr(var_str, '='))
		len[0] = ft_strchr(var_str, '=') - var_str;
	new->name = ft_substr(var_str, 0, len[0]);
	if (!new->name)
		return (free(new), NULL);
	if (len[0] != len[1])
		new->value = ft_substr(var_str, len[0] + 1, len[1] - len[0]);
	if (len[0] != len[1] && !new->value)
		return (del_env_var(new, NULL, NULL), NULL);
	new->display = ft_strdup(var_str);
	if (!new->display)
		return (del_env_var(new, NULL, NULL), NULL);
	return (new);
}

/* Function to add an environment variable to the end of the shell environment
 *
 * @param t_env **env_list	-> pointer to the environment's first variable
 * @param t_env *new		-> pointer to the variable structure to add
 * @return t_env *			-> pointer to the new environment
 */
t_env	*env_add_back(t_env **env_list, t_env *new)
{
	t_env	*temp;

	if (!env_list)
		return (NULL);
	if (!*env_list)
	{
		*env_list = new;
		return (*env_list);
	}
	temp = *env_list;
	while (temp && temp->next)
		temp = temp->next;
	if (temp)
	{
		temp->next = new;
		new->prev = temp;
	}
	return (*env_list);
}

/* Function to update a shell variable structure's value with a new one
 *
 * @parent_function update_env_var
 * @param t_env *env_var	-> pointer to the variable structure to update
 * @param char *value		-> pointer to the update value
 * @param int mode			-> update mode (SH_OVERWRITE/SH_ADDBACK/SH_ADDFRONT)
 * @return int				-> status code of the function
 */
static int	update_env_value(t_env *env_var, char *value, int mode)
{
	char	*temp;

	if (!env_var->value || mode == SH_OVERWRITE)
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
		if (mode == SH_ADDFRONT)
			env_var->value = ft_strjoin(value, temp);
		else
			env_var->value = ft_strjoin(temp, value);
		free(temp);
	}
	if (!env_var->value)
		return (SH_ERROR);
	return (SH_SUCCESS);
}

/* Function to update a variable structure's value + display with a new value
 * mode(SH_OVERWRITE)	-> set the variable to the new value
 * mode(SH_ADDBACK)		-> concatenate the new value after the current value
 * mode(SH_ADDFRONT)	-> concatenate the new value before the current value
 *
 * @child_function update_env_value
 * @param t_env *env_var	-> pointer to the variable structure to update
 * @param char *value		-> pointer to the update value
 * @param int mode			-> update mode (SH_OVERWRITE/SH_ADDBACK/SH_ADDFRONT)
 * @return t_env *			-> pointer to the updated variable structure
 */
t_env	*update_env_var(t_env *env_var, char *value, int mode)
{
	char	*temp;

	if (!env_var)
		return (NULL);
	if (!value && mode != SH_OVERWRITE)
		return (env_var);
	if (update_env_value(env_var, value, mode) != SH_SUCCESS)
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

/* Function to free the allocated memory of a shell environment variable
 *
 * @param t_env *env_var	-> pointer to the variable structure to free
 * @param t_env *prev_var	-> pointer to the previous variable structure
 * @param t_env *next_var	-> pointer to the next variable structure
 */
void	del_env_var(t_env *env_var, t_env *prev_var, t_env *next_var)
{
	if (!env_var)
		return ;
	if (prev_var)
		prev_var->next = next_var;
	if (next_var)
		next_var->prev = prev_var;
	safe_free((void **) &env_var->name);
	safe_free((void **) &env_var->value);
	safe_free((void **) &env_var->display);
	free(env_var);
	env_var = NULL;
}
