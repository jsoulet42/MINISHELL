/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:23:02 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/17 19:45:55 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*prompt(void)
{
	int		lens[2];
	char	*env_value;
	char	prompt[PROMPT_BUFFER];

	ft_bzero(prompt, PROMPT_BUFFER);
	env_value = getenv("USER");
	lens[0] = ft_strlen(env_value);
	if (lens[0] > 0 && lens[0] < PROMPT_BUFFER - 1)
		ft_memmove(prompt, env_value, lens[0] * sizeof(char));
	else
	{
		lens[0] = 5;
		ft_memmove(prompt, "guest", lens[0] * sizeof(char));
	}
	prompt[lens[0]] = '@';
	env_value = getenv("NAME");
	lens[1] = ft_strlen(env_value);
	if (lens[1] > 0 && lens[1] + lens[0] < PROMPT_BUFFER - 5)
	{
		ft_memmove(prompt + lens[0] + 1, env_value, lens[1] * sizeof(char));
		ft_memmove(prompt + lens[0] + lens[1] + 1, " $> ", 4 * sizeof(char));
	}
	else if (lens[0] < PROMPT_BUFFER - 13)
		ft_memmove(prompt + lens[0] + 1, "mishelle $> ", 12 * sizeof(char));
	return (readline(prompt));
}

/*
if (str[0] == '$')
{
	var = getenv(str + 1);
	if (var)
		prinft("%s", var);
	printf("\n")
}
*/
