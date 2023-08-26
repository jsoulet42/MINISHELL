/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:30 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/26 18:11:22 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	get_cmd_path(char **to_set, char **bin_paths, char *cmd)
{
	char	*tmp;

	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) != 0)
			return (SH_ERROR);
		*to_set = cmd;
		return (SH_SUCCESS);
	}
	while (*bin_paths)
	{
		tmp = ft_strjoin(*bin_paths++, "/");
		if (!tmp)
			return (SH_ERROR);
		*to_set = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!*to_set)
			return (SH_ERROR);
		if (access(*to_set, F_OK | X_OK) == 0)
			return (SH_SUCCESS);
		free(*to_set);
		*to_set = NULL;
	}
	return (SH_ERROR + 1);
}

char	*get_path(char *cmd, t_env *env)
{
	int		status;
	char	*cmd_path;
	char	**bin_paths;

	g_shell_data->exit_code = 0;
	bin_paths = ft_split(ft_getenv(env, "PATH"), ':');
	if (!bin_paths)
		return (NULL);
	cmd_path = NULL;
	status = get_cmd_path(&cmd_path, bin_paths, cmd);
	free_str_tab((void **)bin_paths);
	if (errno == 13)
		g_shell_data->exit_code = 126;
	else
		g_shell_data->exit_code = errno;
	if (status == SH_ERROR)
		ft_perror("mishelle", cmd);
	if (status == SH_ERROR + 1)
	{
		ft_fprintf(2, "mishelle: %s: command not found\n", cmd);
		g_shell_data->exit_code = 127;
	}
	errno = 0;
	return (cmd_path);
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

void	run_child(t_rinity *cmd_struct, int *fd, t_env *env)
{
	int	builtin_check;

	close(fd[0]);
	if (!cmd_struct->file_out)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	builtin_check = agent_smith(cmd_struct->cmd[0]);
	if (builtin_check > -1)
	{
		execute_builtin(cmd_struct, builtin_check);
		exit(0);
	}
	else
		execute_cmd(env, cmd_struct);
	exit(130);
}
/*
void	execute_builtin2(t_rinity *cmd_struct, int builtin, t_env *env)
{
	if (builtin == 4)
		ft_env(lentab(cmd_struct->cmd), cmd_struct->cmd, env_to_str_tab(env));
	if (builtin == 5)
		ft_echo(lentab(cmd_struct->cmd), cmd_struct->cmd);
	if (builtin == 6)
		ft_pwd(lentab(cmd_struct->cmd), cmd_struct->cmd);
	exit(0);
}*/
