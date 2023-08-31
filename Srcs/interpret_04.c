/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:44 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/31 20:09:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	get_exit_code(int status_code, int *to_set)
{
	if (WIFEXITED(status_code))
		*to_set = WEXITSTATUS(status_code);
	else if (WIFSIGNALED(status_code))
		*to_set = 128 + WTERMSIG(status_code);
	else
		*to_set = status_code;
}

void	exec_last(t_env *env, t_rinity *cmd, char **envp)
{
	int		builtin_check;
	int		status_code;
	pid_t	pid;

	builtin_check = agent_smith(cmd->cmd[0]);
	if (builtin_check != -1)
	{
		g_shell_data->exit_code = execute_builtin(cmd, builtin_check);
		return ;
	}
	if (redirect_streams(cmd))
		return ((void)envp);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execute_cmd(env, cmd);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, &status_code, 0);
		get_exit_code(status_code, &g_shell_data->exit_code);
	}
}

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

int	execute_builtin(t_rinity *cd, int builtin)
{
	int		status;
	char	**temp_env;

	if (redirect_streams(cd))
		return (1);
	status = 0;
	if (builtin == 0)
		ft_cd(lentab(cd->cmd), cd->cmd, &g_shell_data->env);
	if (builtin == 1)
		status = ft_exit(lentab(cd->cmd), cd->cmd);
	if (builtin == 2)
		status = ft_export(cd->cmd, &g_shell_data->env);
	if (builtin == 3)
		status = ft_unset(cd->cmd, &g_shell_data->env);
	if (builtin == 4)
	{
		temp_env = env_to_str_tab(g_shell_data->env);
		status = ft_env(lentab(cd->cmd), cd->cmd, temp_env);
		free_str_tab((void **) temp_env);
	}
	if (builtin == 5)
		status = ft_echo(lentab(cd->cmd), cd->cmd);
	if (builtin == 6)
		status = ft_pwd(lentab(cd->cmd), cd->cmd);
	return (status);
}
