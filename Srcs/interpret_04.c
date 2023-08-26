/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:44 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/26 11:50:14 by hnogared         ###   ########.fr       */
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
	int		status_code;
	pid_t	pid;

	if (redirect_streams(cmd))
	{
		g_shell_data->exit_code = 1;
		return ((void)envp);
	}
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
	if (!ft_strncmp(cmd, "./minishell", 12))
		return (7);
	return (-1);
}

void	execute_builtin(t_rinity *cd, int builtin)
{
	pid_t	pid;

	if (redirect_streams(cd))
	{
		g_shell_data->exit_code = 1;
		return ;
	}
	if (execute_first_builtin(cd, builtin))
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		continue_child_builtin(cd, builtin);
		exit(0);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, &g_shell_data->exit_code, 0);
	}
}

void	continue_child_builtin(t_rinity *cd, int builtin)
{
	char	**temp_env;

	temp_env = env_to_str_tab(g_shell_data->env);
	if (builtin == 4)
		ft_env(lentab(cd->cmd), cd->cmd, temp_env);
	if (builtin == 5)
		ft_echo(lentab(cd->cmd), cd->cmd);
	if (builtin == 6)
		ft_pwd(lentab(cd->cmd), cd->cmd);
	if (builtin == 7)
		execve(cd->cmd[0], cd->cmd, temp_env);
	free_str_tab((void **) temp_env);
}
