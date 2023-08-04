#include "../../Includes/minishell.h"

void	exec_last(t_env *env, t_rinity *cmd_struct, char **envp)
{
	pid_t	pid;

	(void)envp;
	g_shell_data->path = get_path(cmd_struct->cmd[0], env);
	if (!g_shell_data->path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd_struct->cmd[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		redirect(cmd_struct, 0);
		redirect(cmd_struct, 1);
		execve(g_shell_data->path, cmd_struct->cmd, env_to_str_tab(&env));
	}
	else
	{
		signal(SIGINT, second_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, NULL, 0);
		signal(SIGINT, main_sig_handler);
	}
}

int	agent_smith(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2))
		return (0);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (2);
	if (!ft_strncmp(cmd, "unset", 5))
		return (3);
	if (!ft_strncmp(cmd, "env", 3))
		return (4);
	if (!ft_strncmp(cmd, "echo", 4))
		return (5);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (6);
	return (-1);
}

void	execute_builtin(t_rinity *cd, int builtin)
{
	pid_t	pid;

	if (execute_first_builtin(cd, builtin) == 1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		redirect(cd, 0);
		redirect(cd, 1);
		if (builtin == 5)
			execve("bin/./echo", cd->cmd, env_to_str_tab(&g_shell_data->env));
		if (builtin == 6)
			execve("bin/./pwd", cd->cmd, env_to_str_tab(&g_shell_data->env));
		if (builtin == 4)
			execve("bin/./env", cd->cmd, env_to_str_tab(&g_shell_data->env));
	}
	else
	{
		signal(SIGINT, second_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, NULL, 0);
		signal(SIGINT, main_sig_handler);
	}
}
