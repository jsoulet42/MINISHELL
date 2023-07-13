/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:37:36 by me                #+#    #+#             */
/*   Updated: 2023/07/13 17:15:16 by dw dqw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_env	*get_default_env(char **envp)
{
	int		i;
	t_env	*new_var;
	t_env	*env_list;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_var = new_env_var(envp[i++], NULL);
		if (!new_var)
		{
			free_env(&env_list);
			return (NULL);
		}
		printf("New : %s\n", new_var->var_display);
		env_add_back(&env_list, new_var);
	}
	return (env_list);
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;

	env_list = NULL;
	env_list = get_default_env(envp);
	env_list = new_env_var("TEST=test", NULL);
	if (envp)
		return (env_list);
	return (env_list);
}

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
