/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:09:47 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/11 11:17:34 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	is_operand(const char *str);
t_par **init_parsing(char *argv);
int count_arg(const char *argv);


int main (int argc, char **argv)
{
	int	res;

	if (argc == 1)
		return (0);
	res = count_arg(argv[1]);
	printf("res = %d\n", res);
}

/*t_par **init_parsing(char *argv)
{
	t_par	**parsing;
	int		i;

	i = 0;
	if (!parsing)
		return (NULL); //appeler la fonction qui gere les erreurs
	parsing[argv] = NULL;
	return (par);
}*/

int count_arg(const char *argv)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 1;
	while (argv[i])
	{
		if (argv[i] == ' ' && argv[i + 1] != ' ' && argv[i + 1] != '\n')
			count++;
		j = is_operand(argv + i);
		if (j != 0)
		{
			i += j - 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	is_operand(const char *str)
{
	if (ft_strchr(OPERANDS, *str) != NULL)
	{
		if (str == str + 1)
			return (2);
		return (1);
	}
	return (0);
}
