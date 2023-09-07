/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:31:39 by hnogared          #+#    #+#             */
/*   Updated: 2023/09/04 16:06:53 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	check_line(t_par **par)
{
	int	i;

	i = 0;
	while (par[i])
	{
		if (par[i]->type != 0 && par[i + 1] && par[i + 1]->type != 0)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i + 1]->str));
		}
		if (par[i]->type != 0 && par[i + 1] == NULL)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i]->str));
		}
		i++;
	}
	return (0);
}

int	commande_len(t_par **par)
{
	int	i;
	int	len;

	if (!par)
		return (-1);
	i = 0;
	len = 0;
	while (par[i] && par[i]->type == 1)
		i++;
	while (par[i + len] && par[i + len]->type != 1)
		len++;
	return (len);
}

int	next_good_commande(t_par **par, int i)
{
	int	res;

	res = 0;
	while (par[i] && par[i]->type >= 2 && par[i]->type <= 5)
	{
		i += 2;
		res += 2;
	}
	return (res);
}

char	**create_commande(t_par **par, int i)
{
	int		j;
	int		len;
	char	**commande;

	if (!par)
		return (NULL);
	while (par[i] && par[i]->type >= 2 && par[i]->type <= 5)
		i += 2;
	len = commande_len(par + i);
	if (len == 0)
		return (NULL);
	commande = (char **)malloc(sizeof(char *) * (len + 1));
	if (!commande)
		return (NULL);
	j = 0;
	while (par[i + j] && par[i + j]->type != 1)
	{
		commande[j] = par[i + j]->str;
		j++;
		i += next_good_commande(par, i + j);
	}
	commande[j] = NULL;
	return (commande);
}
