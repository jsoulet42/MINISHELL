/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:26:42 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/14 11:54:55 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to return an environment linked list data as a strings array
 *
 * @param t_env *env_list	-> pointer to the list to convert
 * @return char **			-> pointer to the converted strings array
 */
char	**env_to_str_tab(t_env *env_list)
{
	int		i;
	char	**envp;
	t_env	*start;

	if (!env_list)
		return (NULL);
	start = env_list;
	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	envp = (char **) ft_calloc((i + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (start)
	{
		envp[i++] = ft_strdup(start->display);
		if (!envp[i - 1])
			return (free_str_tab(envp), NULL);
		start = start->next;
	}
	return (envp);
}

/* Function to get the pointer to an environment's variable structure
 * with a given name
 *
 * @param t_env *env_list	-> pointer to the environment linked list
 * @param char *var_name	-> pointer to the variable name to find
 * @return t_env *			-> pointer to the retrieved variable structure
 */
t_env	*get_env_node(t_env *env_list, char *var_name)
{
	int	name_len;

	if (!env_list || !var_name)
		return (NULL);
	name_len = ft_strlen(var_name);
	while (env_list && ft_strncmp(env_list->name, var_name, name_len))
		env_list = env_list->next;
	return (env_list);
}

/* Function to update a variable structure value
 *
 */
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
