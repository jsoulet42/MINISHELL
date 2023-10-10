/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:15:57 by jsoulet           #+#    #+#             */
/*   Updated: 2023/10/05 15:52:50 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	agent_smith(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3))
		return (0);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (2);
	if (!ft_strncmp(cmd, "unset", 6))
		return (3);
	if (!ft_strncmp(cmd, "env", 4))
		return (4);
	if (!ft_strncmp(cmd, "echo", 5))
		return (5);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (6);
	return (-1);
}

int	execute_builtin(t_rinity *cd)
{
	if (cd->builtin == 0)
		return (ft_cd(str_tab_len(cd->cmd), cd->cmd, &g_shell_data.env));
	if (cd->builtin == 1)
		return (ft_exit(str_tab_len(cd->cmd), cd->cmd));
	if (cd->builtin == 2)
		return (ft_export(cd->cmd, &g_shell_data.env));
	if (cd->builtin == 3)
		return (ft_unset(cd->cmd, &g_shell_data.env));
	if (cd->builtin == 4)
		return (ft_env(str_tab_len(cd->cmd), cd->cmd, &g_shell_data.env));
	if (cd->builtin == 5)
		return (ft_echo(str_tab_len(cd->cmd), cd->cmd));
	if (cd->builtin == 6)
		return (ft_pwd(str_tab_len(cd->cmd), cd->cmd));
	return (SH_SUCCESS);
}

void	execute_cmd(t_env *env, t_rinity *cmd_struct)
{
	char	**str_env;

	str_env = env_to_str_tab(env);
	if (!str_env)
		exit(errno);
	execve(cmd_struct->cmd_path, cmd_struct->cmd, str_env);
	ft_perror("mishelle", cmd_struct->cmd[0]);
	free_str_tab((void **)str_env);
	exit(errno);
}

void	get_exit_code(int status_code, int *to_set)
{
	if (WIFEXITED(status_code))
	{
		*to_set = WEXITSTATUS(status_code);
		*to_set += 113 * (*to_set == 13);
	}
	else if (WIFSIGNALED(status_code))
		*to_set = 128 + WTERMSIG(status_code);
	else
		*to_set = status_code;
}
