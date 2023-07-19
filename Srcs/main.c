/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/19 16:29:00 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell	*g_shell_data;

void exec_last(t_env *env);

int count_cmd(t_par **par)
{
	int i;
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
}

int	init_data(char **envp)
{
	g_shell_data = (t_shell *) ft_calloc(sizeof(t_shell), 1);
	if (!g_shell_data)
		return (1);
	init_env(&g_shell_data->env, envp);
	g_shell_data->in = dup(STDIN_FILENO);
	g_shell_data->out = dup(STDOUT_FILENO);
	g_shell_data->commande = NULL;
	//g_shell_data->fd[0] = 0;
	//g_shell_data->fd[1] = 0;
	return (0);
}

static int	prompt_cmd(void)
{
	char	*line;
	char	*line2;
	int		cmd;

	//dup2(g_shell_data->in, STDIN_FILENO);
	//dup2(g_shell_data->out, STDOUT_FILENO);
	//dup2(g_shell_data->fd[0], STDIN_FILENO);
	line = prompt();
	if (!line)
		return (1);
	if (!*line)
		return (0);
	add_history(line);
	line2 = ft_strtrim(line, " \n\t\v");
	free(line);
	if (check_starterrors(line2) > 0)
		return (free(line2), 1);
	g_shell_data->par = ft_parsing(line2);
	free(line2);
	check_line(g_shell_data->par);
	cmd = count_cmd(g_shell_data->par);
	while (cmd > 1)
	{
		g_shell_data->commande = create_commande(g_shell_data->par);
		//print_str_tab(g_shell_data->commande);
		piper(g_shell_data->env);
		cmd--;
	}
	g_shell_data->commande = create_commande(g_shell_data->par);
	exec_last(g_shell_data->env);
	//exec_last(g_shell_data->env);
	dup2(g_shell_data->in, STDIN_FILENO);
	//dup2(1, STDOUT_FILENO);
	//exec_last(g_shell_data->env);
	//dup2(1, STDOUT_FILENO);
	//dup2(g_shell_data->in, STDIN_FILENO);
	//dup2(g_shell_data->out, STDOUT_FILENO);
	free_t_par(g_shell_data->par);
	return (0);
}

void exec_last(t_env *env)
{
	char *path;
	pid_t pid;

	path = get_path(g_shell_data->commande[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(g_shell_data->commande[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execve(path, g_shell_data->commande, env_to_str_tab(env));
		else
			waitpid(pid, NULL, 0);
	}
}
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (init_data(envp))
		return (1);
	print_env(g_shell_data->env, SH_DISORDERED);
	free_data(g_shell_data);
	return (0);
	while (1)
	{
		if (prompt_cmd())
			return (free_data(g_shell_data), 1);
	}
	free_env(&g_shell_data->env);
	return (0);
}
