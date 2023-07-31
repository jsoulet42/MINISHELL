/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/29 15:09:21 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell *g_shell_data;

int init_data(char **envp)
{
	g_shell_data = (t_shell *)ft_calloc(sizeof(t_shell), 1);
	if (!g_shell_data)
		return (1);
	modif_shlvl(envp);
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	return (0);
}

static int prompt_cmd(char **envp)
{
	char *line;
	char *line2;
	int i;

	line = prompt(g_shell_data->env);
	if (!line || !*line)
		return (line2 = line, safe_free((void **)&line), !line2);
	add_history(line);
	line2 = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (check_starterrors(line2) > 0)
		return (free(line2), 0);
	g_shell_data->t = ft_parsing(line2);
	free(line2);
	i = 0;
	while (g_shell_data->t[i + 1])
		piper(g_shell_data->env, g_shell_data->t[i++]);
	exec_last(g_shell_data->env, g_shell_data->t[i], envp);
	safe_free((void **)&g_shell_data->path);
	dup2(g_shell_data->in, STDIN_FILENO);
	dup2(g_shell_data->out, STDOUT_FILENO);
	free_t_par(g_shell_data->par);
	return (0);
}

void exec_last(t_env *env, t_rinity *cmd_struct, char **envp)
{
	pid_t pid;

	(void)envp;
	g_shell_data->path = get_path(cmd_struct->command[0], env);
	if (ft_strncmp(cmd_struct->command[0], "cd", 2) == 0)
		ft_cd(lentab(cmd_struct->command), cmd_struct->command, env);
	else if (ft_strncmp(cmd_struct->command[0], "export", 6) == 0)
		ft_export(cmd_struct->command, &env);
	else if (ft_strncmp(cmd_struct->command[0], "unset", 5) == 0)
		ft_unset(cmd_struct->command, &env);
	else if (ft_strncmp(cmd_struct->command[0], "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(cmd_struct->command[0], "env", 3) == 0)
		ft_env(envp);
	else if (!g_shell_data->path)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: command not found: `%s'\n",
			cmd_struct->command[0]);
		return ;
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(cmd_struct, 0);
			redirect(cmd_struct, 1);
			execve(g_shell_data->path, cmd_struct->command, env_to_str_tab(env));
		}
		else
		{
			signal(SIGINT, second_sig_handler);
			dup2(g_shell_data->out, STDOUT_FILENO);
			waitpid(pid, NULL, 0);
			signal(SIGINT, main_sig_handler);
		}
	}
}

/*
 * SIGQUIT -> Ctrl-\ signal which needs to be ignored
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, main_sig_handler);
	if (init_data(envp))
		return (1);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	while (1)
	{
		if (prompt_cmd(envp))
			return (free_data(g_shell_data), 1);
		envp = env_update(envp, g_shell_data);
	}
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	free_data(g_shell_data);
	return (0);
}

