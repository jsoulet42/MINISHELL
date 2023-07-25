/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_starterrors02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:51:18 by lolefevr          #+#    #+#             */
/*   Updated: 2023/07/25 17:00:23 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	unknown_command()
{
	printf("Error : Unknown command type \n");
	return (1);// apel du builtin exit.
}

int viveldop(int gel, char *str, int *i)
{
	if (str[*(i) + 1] == gel)
		return (1);
	return (0);
}

int error_gen(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 34)
			dblequote(&i, str);
		if (str[i] == 39)
			simplequote(&i, str);
		if ((((str[i] == 92) || str[i] == 40) || str[i] == 59) || str[i] == 41)
			return (unknown_command());
		if ((str[i] == '&' || str[i] == '|') && (viveldop(str[i], str, &i) > 0))
			return (unknown_command());
		i++;
	}
	return (0);
}

int error_pipe(char *str)
{
	int	i;

	i = 0;

	while (str[i + 1] != 0)
		i++;
	if (((str[i] == '|') || str[i] == '>') || str[i] == '<')
	{
		printf("Error : False redirection\n");
		return (1);// apel du builtin exit.
	}
	return (0);
}

int	check_starterrors(char *str)
{
	if (error_quote(str) || error_gen(str, 0) || error_pipe(str))
		return (1);
	else
		return (0);
}
