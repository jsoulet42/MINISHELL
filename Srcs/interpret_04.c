/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:44 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/20 20:02:38 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	exec_last(t_env *env, t_rinity *cmd, char **envp)
{
	pid_t	pid;

	g_shell_data->path = get_path(cmd->cmd[0], env);
	if (!g_shell_data->path)
	{
		g_shell_data->exit_code = 127;
		ft_fprintf(2, "mishelle: %s : command not found \n", cmd->cmd[0]);
		return ((void) envp);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (redirect_streams(cmd))
			exit(1);
		execve(g_shell_data->path, cmd->cmd, env_to_str_tab(env));
		exit(127);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, &g_shell_data->exit_code, 0);
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

	if (execute_first_builtin(cd, builtin))
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		redirect_streams(cd);
		continue_child_builtin(cd, builtin);
		exit(0);
	}
	else
	{
		signal(SIGQUIT, parent_sig_handler);
		signal(SIGINT, parent_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, NULL, 0);
		g_shell_data->exit_code = 0;
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
