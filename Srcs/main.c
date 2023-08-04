
#include "../Includes/minishell.h"

t_shell *g_shell_data;

int	init_data(char **envp)
{
	g_shell_data = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!g_shell_data)
		return (1);
/*	if (!envp)
		return (1);*/
	modif_shlvl(envp);
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	return (0);
}

static int prompt_cmd(char **envp)
{
	char	*line;
	char	*line2;
	int		i;

	if (!envp)
		return (1);
	line = prompt(g_shell_data->env);
	if (!line || !*line)
		return (line2 = line, safe_free((void **)&line), !line2);
	add_history(line);
	line2 = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (check_starterrors(line2) > 0)
		return (free(line2), 1);
	ft_fprintf(2,"ok\n");
	free_trinity();
	g_shell_data->t = ft_parsing(line2);
	free(line2);
	i = 0;
	while (g_shell_data->t && g_shell_data->t[i + 1])
		piper(g_shell_data->env, g_shell_data->t[i++]);
	if (agent_smith(g_shell_data->t[i]->command[0]) != -1)
		execute_builtin(g_shell_data->t[i], g_shell_data->t[i]->builtin);
	else
		exec_last(g_shell_data->env, g_shell_data->t[i], envp);
	safe_free((void **)&g_shell_data->path);
	dup2(g_shell_data->in, STDIN_FILENO);
	dup2(g_shell_data->out, STDOUT_FILENO);
	free_t_par(g_shell_data->par);
	return (0);
}

int agent_smith(char *cmd)
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
void execute_builtin(t_rinity *cmd_struct, int builtin)
{
	pid_t pid;

	if (execute_first_builtin(cmd_struct, builtin) == 1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		redirect(cmd_struct, 0);
		redirect(cmd_struct, 1);
		if (builtin == 5)
			execve("bin/./echo", cmd_struct->command, env_to_str_tab(&g_shell_data->env));
		if (builtin == 6)
			execve("bin/./pwd", cmd_struct->command, env_to_str_tab(&g_shell_data->env));
		if (builtin == 4)
			execve("bin/./env", cmd_struct->command, env_to_str_tab(&g_shell_data->env));
	}
	else
	{
		signal(SIGINT, second_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, NULL, 0);
		signal(SIGINT, main_sig_handler);
	}
}

int	execute_first_builtin(t_rinity *cmd_struct, int builtin)
{
		if (builtin == 1)
		{
			ft_exit(cmd_struct->command);
			return (1);
		}
		else if (builtin == 2)
		{
			ft_export(cmd_struct->command, &g_shell_data->env);
			return (1);
		}
		else if (builtin == 3)
		{
			ft_unset(cmd_struct->command, &g_shell_data->env);
			return (1);
		}
		else if (builtin == 0)
		{
			ft_cd(lentab(cmd_struct->command), cmd_struct->command, &g_shell_data->env);
			return (1);
		}
		else
			return (0);
}

void exec_last(t_env *env, t_rinity *cmd_struct, char **envp)
{
	pid_t	pid;

	(void)envp;
	g_shell_data->path = get_path(cmd_struct->command[0], env);
	if (!g_shell_data->path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd_struct->command[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		redirect(cmd_struct, 0);
		redirect(cmd_struct, 1);
		execve(g_shell_data->path, cmd_struct->command, env_to_str_tab(&env));
	}
	else
	{
		signal(SIGINT, second_sig_handler);
		dup2(g_shell_data->out, STDOUT_FILENO);
		waitpid(pid, NULL, 0);
		signal(SIGINT, main_sig_handler);
	}
}

/*
 * SIGQUIT -> Ctrl-\ signal which needs to be ignored
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	*test;

	signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, main_sig_handler);
	signal(SIGINT, main_sig_handler);
	if (init_data(envp))
		return (1);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	while (1)
	{
		if (prompt_cmd(envp))
			continue;
		test = g_shell_data;
		envp = env_update(envp, test);
	}
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	return (0);
}
