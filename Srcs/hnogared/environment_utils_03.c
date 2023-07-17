/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:51:38 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/16 19:09:24 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/hnogared.h"

/* Function to display the environment in alphabetical order on terminal
 *
 * @param t_env *env_list	-> pointer to the environment to display
 */
void	print_ordered_env(t_env *env_list)
{
	char	**temp;
	char	**str_env;

	if (!env_list)
		return ;
	str_env = env_to_str_tab(env_list);
	if (!str_env)
		return ;
	order_str_tab(str_env);
	temp = str_env;
	while (*temp)
		printf("%s\n", *temp++);
	free_str_tab(str_env);
}
