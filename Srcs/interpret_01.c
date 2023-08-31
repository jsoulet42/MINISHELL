/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:15:57 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/30 20:58:59 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_line_words(const char **line_tab)
{
	int		test;
	int		test2;
	char	**temp;

	if (!line_tab || !*line_tab)
		return (SH_ERROR);
	temp = (char **)line_tab - 1;
	while (*(++temp))
	{
		test = ft_isoperand(**temp);
		if (*(temp + 1))
			test2 = ft_isoperand(*(temp + 1)[0]);
		if (test && (!*(temp + 1) || test2))
		{
			printf("mishelle: syntax error bad operand `");
			printf("%s'\n", *temp);
			return (SH_ERROR);
		}
	}
	return (SH_SUCCESS);
}
/*
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
*/
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

void	execute_cmd(t_env *env, t_rinity *cmd_struct)
{
	char	**str_env;

	g_shell_data->path = get_path(cmd_struct->cmd[0], env);
	if (!g_shell_data->path)
		exit(g_shell_data->exit_code);
	str_env = env_to_str_tab(env);
	execve(g_shell_data->path, cmd_struct->cmd, str_env);
	ft_perror("mishelle", cmd_struct->cmd[0]);
	free_str_tab((void **)str_env);
	exit(errno);
}
