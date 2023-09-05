/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:44 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/04 16:27:20 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	run_child(t_rinity *cmd_struct, int *fd, t_env *env)
{
	int	builtin_check;

	close(fd[0]);
	if (!cmd_struct->file_out)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	builtin_check = agent_smith(cmd_struct->cmd[0]);
	if (builtin_check > -1)
		exit(execute_builtin(cmd_struct, builtin_check));
	else
		execute_cmd(env, cmd_struct);
	exit(0);
}

static int	ft_fork(pid_t pid, int *fd, t_rinity *cmd_struct, t_env *env)
{
	int	status_code;

	status_code = 0;
	if (pid == -1)
	{
		g_shell_data->exit_code = errno;
		return (perror("mishelle"), SH_ERROR);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		run_child(cmd_struct, fd, env);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		waitpid(pid, &status_code, 0);
		get_exit_code(status_code, &g_shell_data->exit_code);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (status_code);
}

int	piper(t_env *env, t_rinity *cmd_struct)
{
	int		status_code;
	int		fd[2];
	pid_t	pid;

	if (redirect_streams(cmd_struct))
		return (SH_ERROR);
	if (pipe(fd) == -1)
	{
		g_shell_data->exit_code = errno;
		return (perror("mishelle"), SH_ERROR);
	}
	pid = fork();
	status_code = ft_fork(pid, fd, cmd_struct, env);
	return (status_code);
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
