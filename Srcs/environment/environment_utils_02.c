/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:14:05 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 14:40:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* Function to retrieve a variable's value inside a shell's environment
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

/* Function to return a shell environment's data as a strings array
 *
 * @param t_env *env_list	-> pointer to the list to convert
 * @return char **			-> pointer to the converted strings array
 */
char	**env_to_str_tab(t_env *env_list)
{
	int		i;
	char	**envp;
	t_env	*temp;

	if (!env_list)
		return (NULL);
	temp = env_list;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	envp = (char **) ft_calloc((i + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		envp[i++] = ft_strdup(env_list->display);
		if (!envp[i - 1])
			return (free_str_tab((void **)envp), NULL);
		env_list = env_list->next;
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

/* Function to display an environment's linked list of variables on terminal
 * following a given mode
 * mode(SH_DISORDERED)	-> display only the variables with a value disorderly
 * mode(SH_ORDERED)		-> display variables in alphabetical order the export way
 *
 * @param t_env *env_list	-> pointer to the environment to display
 * @param int mode			-> display mode of the environment
 */
void	print_env(t_env *env_list, int mode)
{
	char	*check;
	char	**temp;
	char	**str_env;

	if (mode == SH_ORDERED)
	{
		str_env = order_str_tab(env_to_str_tab(env_list), '=');
		if (!str_env)
			return ;
		temp = str_env - 1;
		while (*(++temp))
		{
			check = ft_strchr(*temp, '=');
			mode = '"' * (check && !*(check + 1));
			if ((*temp)[0] != '_' || ((*temp)[1] && (*temp)[1] != '='))
				printf("declare -x %s%c%c\n", *temp, mode, mode);
		}
		return (free_str_tab((void **) str_env));
	}
	while (env_list)
	{
		if (ft_strchr(env_list->display, '='))
			printf("%s\n", env_list->display);
		env_list = env_list->next;
	}
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
