/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:44 by jsoulet           #+#    #+#             */
/*   Updated: 2023/09/21 15:32:35 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	run_child(t_rinity *cmd_struct, int *fd, t_env *env)
{
	close(fd[0]);
	if (!cmd_struct->file_out)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cmd_struct->builtin != -1)
		exit(execute_builtin(cmd_struct));
	else
		execute_cmd(env, cmd_struct);
	exit(0);
}

static void	ft_fork(pid_t pid, int *fd, t_rinity *cmd_struct, t_env *env)
{
	int	status_code;

	if (pid == -1)
	{
		g_shell_data.exit_code = errno;
		return (perror("mishelle"));
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		set_termios_mode(TERMIOS_UNMUTE_CTRL, g_shell_data.default_termios);
		run_child(cmd_struct, fd, env);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		waitpid(pid, &status_code, 0);
		get_exit_code(status_code, &g_shell_data.exit_code);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		set_termios_mode(TERMIOS_MUTE_CTRL, g_shell_data.default_termios);
	}
}

void	piper(t_env *env, t_rinity *cmd_struct)
{
	int		fd[2];
	pid_t	pid;

	if (redirect_streams(cmd_struct))
		return ;
	cmd_struct->builtin = agent_smith(cmd_struct->cmd[0]);
	if (cmd_struct->builtin == -1)
	{
		cmd_struct->cmd_path = get_path(cmd_struct->cmd[0], env);
		if (!cmd_struct->cmd_path)
			return ;
	}
	if (pipe(fd) == -1)
	{
		g_shell_data.exit_code = errno;
		return (perror("mishelle"));
	}
	pid = fork();
	ft_fork(pid, fd, cmd_struct, env);
}

static void	ft_last_fork(pid_t pid, t_rinity *cmd, t_env *env)
{
	int	status_code;

	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		set_termios_mode(TERMIOS_UNMUTE_CTRL, g_shell_data.default_termios);
		execute_cmd(env, cmd);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		dup2(g_shell_data.out, STDOUT_FILENO);
		waitpid(pid, &status_code, 0);
		get_exit_code(status_code, &g_shell_data.exit_code);
		set_termios_mode(TERMIOS_MUTE_CTRL, g_shell_data.default_termios);
	}
}

void	exec_last(t_env *env, t_rinity *cmd)
{
	pid_t	pid;

	if (redirect_streams(cmd))
		return ;
	cmd->builtin = agent_smith(cmd->cmd[0]);
	if (cmd->builtin != -1)
	{
		g_shell_data.exit_code = execute_builtin(cmd);
		return ;
	}
	cmd->cmd_path = get_path(cmd->cmd[0], env);
	if (!cmd->cmd_path)
		return ;
	pid = fork();
	ft_last_fork(pid, cmd, env);
}
