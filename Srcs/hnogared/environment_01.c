/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:37:36 by me                #+#    #+#             */
/*   Updated: 2023/07/13 18:48:48 by dw dqw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static t_env	*get_default_env(char **envp)
{
	int		i;
	t_env	*new_var;
	t_env	*env_list;

	if (!envp || !*envp)
		return (NULL);
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_var = new_env_var(envp[i++], NULL);
		if (!new_var)
		{
			free_env(&env_list);
			return (NULL);
		}
		env_add_back(&env_list, new_var);
	}
	return (env_list);
}

//static t_env	*complete_env(t_env **env)

t_env	*init_env(t_env **env_list, char **envp)
{
	*env_list = get_default_env(envp);
//	complete_env(&env_list);
	return (*env_list);
}

/*
void	print_str_tab(char **str_tab)
{
	if (!str_tab)
		return ;
	while (*str_tab)
		printf("%s\n", *str_tab++);
}

void	free_str_tab(char **str_tab)
{
	int	i;

	if (!str_tab)
		return ;
	i = 0;
	while (str_tab[i])
		free(str_tab[i++]);
	free(str_tab);
	str_tab = NULL;
}
*/
