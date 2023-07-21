/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/21 11:20:46 by mdiamant         ###   ########.fr       */
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
	return (0);
}

static int	prompt_cmd(void)
{
	char	*line;
	char	*line2;
	int		i;

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
	i = 0;
	while (g_shell_data->t[i + 1])
	{
		ft_fprintf(2, "while: i = %d\n", i);
		piper(g_shell_data->env, g_shell_data->t[i++]);
	}
	ft_fprintf(2, "sortie: i = %d\n", i);
	exec_last(g_shell_data->env, g_shell_data->t[i]);
	ft_fprintf(2, "apres exec_last\n");
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
	fd_in = create_fd_in(cmd_struct->file_in, cmd_struct->type_in, 1);
	if (fd_in != -1)
		dup2(fd_in, STDIN_FILENO);
	path = get_path(cmd_struct->command[0], env);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: command not found: `%s'\n",
			cmd_struct->command[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd_struct->command, env_to_str_tab(env));
	}
	else
		waitpid(pid, NULL, 0);
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
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sig_handler);
		if (prompt_cmd())
			return (free_data(g_shell_data), 1);
	}
	free_data(g_shell_data);
	return (0);
}
