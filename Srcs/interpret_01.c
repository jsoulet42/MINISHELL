/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:15:57 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/15 15:45:01 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
	g_shell_data->path = get_path(cmd_struct->cmd[0], env);
	if (!g_shell_data->path)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: command not found: `%s'\n",
			cmd_struct->cmd[0]);
		g_shell_data->exit_code = 127;
		exit (0);
	}
	execve(g_shell_data->path, cmd_struct->cmd, env_to_str_tab(env));
}
