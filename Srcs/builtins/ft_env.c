/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:56:06 by lolefevr          #+#    #+#             */
/*   Updated: 2023/08/02 14:43:02 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_env(t_env	*env)
{
	t_env	*temp;
	int	len;
	temp = env;
	while (temp)
	{
		if (temp->name)
			printf("%s", temp->name);
		len = strlen(temp->name);
		if (temp->name[len] != '=')
			printf("=");
		if (temp->value)
			printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (0);
}
