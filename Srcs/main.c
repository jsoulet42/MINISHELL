/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:59:01 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/20 09:17:36 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_shell	*g_shell_data;

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
	return (0);
}

static int	prompt_cmd(void)
{
	char	*line;
	char	*line2;
	int		cmd;

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
		piper(g_shell_data->env);
		cmd--;
	}
	g_shell_data->commande = create_commande(g_shell_data->par);
	exec_last(g_shell_data->env);
	dup2(g_shell_data->in, STDIN_FILENO);
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
	while (1)
	{
		if (prompt_cmd())
			return (free_data(g_shell_data), 1);
	}
	free_env(&g_shell_data->env);
	return (0);
}
