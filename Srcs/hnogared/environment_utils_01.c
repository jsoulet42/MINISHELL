/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:08:06 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/18 18:00:27 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to retrieve a variable's value inside the minishell's environment
 *
 * @param t_env *env		-> pointer to the source environment linked list
 * @param char *var_name	-> pointer to the variable name to search for
 * @return char *			-> pointer to the variable value to retrieve
 */
char	*ft_getenv(t_env *env, char *var_name)
{
	t_env	*found;

	if (!env || !var_name)
		return (NULL);
	found = get_env_var(env, var_name);
	if (found)
		return (found->value);
	return (NULL);
}

/* Function to allocate a minishell environment variable with a given value
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

/* Function to add an environment variable to the end of the environment
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
	temp = *env_list;
	while (temp && temp->next)
		temp = temp->next;
	if (temp)
	{
		temp->next = new;
		new->prev = temp;
	}
	else
		*env_list = new;
	return (*env_list);
}

/* Function to free the allocated memory of an environment variable
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

/* Function to free the minishell's environment linked list
 *
 * @param t_env **env_list	-> pointer to the environment's first element
 */
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
