/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:30:07 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/24 23:21:46 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int next_cmd(t_par **par);

/*si il y a plusieur operateur de suite on print une erreur
	et on return le print de l'erreur*/
int check_line(t_par **par)
{
	int i;

	i = 0;
	while (par[i])
	{
		if (par[i]->type != 0 && par[i + 1] && par[i + 1]->type != 0)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i + 1]->str));
		}
		if (par[i]->type != 0 && par[i + 1] == NULL)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i]->str));
		}
		i++;
	}
	return (0);
}

int commande_len(t_par **par)
{
	int i;
	int len;

	if (!par)
		return (0);
	i = 0;
	len = 0;
	while (par[i] && par[i]->type == 1)
		i++;
	while (par[i + len] && par[i + len]->type != 1)
		len++;
	return (len);
}

/* on met dans un char **la prochaine commande a execve
	 et si cette fonction return NULL c'est qu'il n'y a plus de commande
		et donc que le programme doit s'arreter */
char **create_commande(t_par **par)
{
	int j;
	int i;
	int len;
	char **commande;

	if (!par)
		return (NULL);
	if (g_shell_data->commande != NULL)
	{
		free(g_shell_data->commande);
		g_shell_data->commande = NULL;
	}
	len = commande_len(par);
	if (len == 0)
		return (NULL);
	commande = (char **)malloc(sizeof(char *) * (len + 1));
	if (!commande)
		return (NULL);
	j = 0;
	i = next_cmd(par);
	while (par[i + j] && par[i + j]->type != 1)
	{
		commande[j] = par[i + j]->str;
		if (par[i + j + 1] && par[i + j + 1]->type >= 2 && par[i + j + 1]->type <= 5)
			i += 2;
		j++;
	}
	commande[j] = NULL;
	return (commande);
}

int next_cmd(t_par **par)
{
	int i;

	i = 0;
	while (par[i])
	{
		if (par[i]->command_elem_id == 1)
		{
			par[i]->command_elem_id = 0;
			return (i);
		}
		i++;
	}
	return (i);
}

void execute_cmd(t_env *env, t_rinity *cmd_struct)
{
	char *path;

	path = get_path(cmd_struct->command[0], env);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: command not found: `%s'\n",
			cmd_struct->command[0]);
		return ;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd_struct->command, env_to_str_tab(env));
}

char *get_path(char *cmd, t_env *env)
{
	char *var;
	char **path;
	char *path_cmd;

	var = ft_getenv(env, "PATH");
	if (!var)
		return (NULL);
	path = ft_split(var, ':');
	path_cmd = get_path_cmd(path, cmd);
	free_str_tab(path);
	return (path_cmd);
}

char *get_path_cmd(char **path, char *cmd)
{
	int i;
	char *path_cmd;
	char *tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path_cmd)
			return (NULL);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

void piper(t_env *env, t_rinity *cmd_struct)
{
	int fd_in;
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		return;
	pid = fork();
	if (pid == -1)
		return;
	if (cmd_struct->file_in && cmd_struct->type_in)
		fd_in = create_fd_in(cmd_struct->file_in, cmd_struct->type_in, 1);
	else
		fd_in = STDIN_FILENO;
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_cmd(env, cmd_struct);
	}
	else
	{
		signal(SIGINT, parent_sig_handler);
		signal(SIGQUIT, parent_sig_handler);
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], fd_in);
		close(fd[0]);
	}
}

int create_fd_in(char **file_in, char **type_in, int t_fd_in)
{
	int i;

	i = 0;
	if (!file_in || !type_in)
		return (-1);
	while (file_in[i])
	{
		if (type_in[i] && ft_strncmp(type_in[i], "<<", 3) == 0)
			ft_heredoc(file_in[i], t_fd_in);
		else if (type_in[i] && ft_strncmp(type_in[i], "<", 2) == 0)
			append_file_content(file_in[i], t_fd_in);
		else
			return (0);
		i++;
	}
	return (0);
}

int append_file_content(char *file, int fd)
{
	int file_fd;
	char c;

	file_fd = -1;
	if (file)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
		{
			ft_fprintf(STDERR_FILENO, "mishelle: `%s': No such file or directory\n");
			return (1);
		}
		while (read(file_fd, &c, 1) > 0)
			write(fd, &c, 1);
	}
	close(file_fd);
	return (0);
}

int	ft_heredoc(char *str, int fd)
{
	char	*line;

	if (fd == -1)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
			break;
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	safe_free((void **)&line);
	return (0);
}
