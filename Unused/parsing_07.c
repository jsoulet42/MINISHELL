/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_07.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:25:02 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 12:29:57 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_quote(char *argv)
{
	if (argv[0] == '\'')
		return (simplquote(argv + 1));
	else if (argv[0] == '"')
		return (doublquote(argv + 1));
	return (-1);
}

int	is_quote_zero(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] == '\'')
	{
		while (argv[i])
		{
			if ((int)argv[i] == 39)
				return (i);
			i++;
		}
	}
	else if (argv[0] == '"')
	{
		while (argv[i])
		{
			if ((int)argv[i] == 34)
				return (i);
			i++;
		}
	}
	return (0);
}

int	verifquote(char *argv)
{
	if (argv[0] == '\'' || argv[0] == '\"')
		return (1);
	return (0);
}

void	free_t_par(t_par **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]->str);
		free(p[i]);
		i++;
	}
	free(p);
	p = NULL;
}

void	ft_addchar(char **str, int i, char *c)
{
	char	*tmp1;
	char	*tmp2;

	tmp2 = ft_substr(*str, 0, i + 1);
	tmp1 = ft_strjoin_plus(tmp2, c);
	free(tmp2);
	tmp2 = ft_substr(*str, i + ft_strlen(c), ft_strlen(*str));
	free(*str);
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}
