/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/24 23:21:27 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell	*g_shell_data;

/*int	count_cmd(t_par **par)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (par[i])
	{
		if (par[i]->command_elem_id == 1)
			j++;
		i++;
	}
	return (j);
}*/

int	init_data(char **envp)
{
	g_shell_data = (t_shell *) ft_calloc(sizeof(t_shell), 1);
	if (!g_shell_data)
		return (1);
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	g_shell_data->commande = NULL;
	set_termios_mode(TERMIOS_MUTE_CTRL);
	return (0);
}

static int	prompt_cmd(void)
{
	char	*line;
	char	*line2;
	int		i;
	//int 	fd[2];

	line = prompt(g_shell_data->env);
	if (!line || !*line)
		return (line2 = line, safe_free((void **) &line), !line2);
	add_history(line);
	line2 = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (check_starterrors(line2) > 0)
		return (free(line2), 1);
	g_shell_data->t = ft_parsing(line2);
	free(line2);
	//fd[0] = dup(g_shell_data->in);
	//fd[1] = dup(g_shell_data->out);
	i = 0;
	while (g_shell_data->t[i + 1])
		piper(g_shell_data->env, g_shell_data->t[i++]);
	exec_last(g_shell_data->env, g_shell_data->t[i]);
	dup2(g_shell_data->in, STDIN_FILENO);
	free_t_par(g_shell_data->par);
	return (0);
}

void	exec_last(t_env *env, t_rinity *cmd_struct)
{
	char	*path;
	pid_t	pid;
	int		fd_in;

	if (!cmd_struct)
		return ;
	path = get_path(cmd_struct->command[0], env);
	fd_in = create_fd_in(cmd_struct->file_in, cmd_struct->type_in, 1);
	if (fd_in != -1)
		dup2(fd_in, STDIN_FILENO);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: command not found: `%s'\n",
			cmd_struct->command[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd_struct->command, env_to_str_tab(env));
	}
	else
	{
		signal(SIGINT, parent_sig_handler);
		signal(SIGQUIT, parent_sig_handler);
		waitpid(pid, NULL, 0);
	}
}

/*
 * SIGQUIT -> Ctrl-\ signal which needs to be ignored
 */
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (init_data(envp))
		return (1);
	set_termios_mode(TERMIOS_MUTE_CTRL);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, main_sig_handler);
		if (prompt_cmd())
			return (free_data(g_shell_data), 1);
	}
	set_termios_mode(TERMIOS_UNMUTE_CTRL);
	free_data(g_shell_data);
	return (0);
}
