/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:30:07 by jsoulet           #+#    #+#             */
/*   Updated: 2023/07/25 19:12:24 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int next_good_commande(t_par **par, int i);

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
			// appel de la fonction exit a la place de return
		}
		if (par[i]->type != 0 && par[i + 1] == NULL)
		{
			printf("minishell: syntax error bad operand `");
			return (printf("%s'\n", par[i]->str));
			// appel de la fonction exit a la place de return
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
		return (-1);
	i = 0;
	len = 0;
	while (par[i] && par[i]->type == 1)
		i++;
	/*if (par[i]->type >= 2 && par[i]->type <= 5)
		i +=2;*/
	while (par[i + len] && par[i + len]->type != 1)
		len++;
	return (len);
}

/* on met dans un char **la prochaine commande a execve
	 et si cette fonction return NULL c'est qu'il n'y a plus de commande
		et donc que le programme doit s'arreter */
char **create_commande(t_par **par, int i)
{
	int j;
	int len;
	char **commande;

	if (!par)
		return (NULL);
	if (g_shell_data->commande != NULL)
	{
		free(g_shell_data->commande);
		g_shell_data->commande = NULL;
	}
	while (par[i] && par[i]->type >= 2 && par[i]->type <= 5)
		i += 2;
	len = commande_len(par + i);
	if (len == 0)
		return (NULL);
	commande = (char **)malloc(sizeof(char *) * (len + 1));
	if (!commande)
		return (NULL);
	j = 0;
	while (par[i + j] && par[i + j]->type != 1)
	{
		commande[j] = par[i + j]->str;
		j++;
		i += next_good_commande(par, i + j);
	}
	commande[j] = NULL;
	return (commande);
}

int next_good_commande(t_par **par, int i)
{
	int res;

	res = 0;
	while (par[i] && par[i]->type >= 2 && par[i]->type <= 5)
	{
		i += 2;
		res += 2;
	}
	return (res);
}
void execute_cmd(t_env *env, t_rinity *cmd_struct)
{
	char *path;

	path = get_path(cmd_struct->command[0], env);
	if (ft_strncmp(cmd_struct->command[0], "cd", 2) == 0)
		ft_cd(lentab(cmd_struct->command), cmd_struct->command, env);
	else if (ft_strncmp(cmd_struct->command[0], "export", 6) == 0)
		ft_export(cmd_struct->command, &env);
	else if (ft_strncmp(cmd_struct->command[0], "unset", 5) == 0)
		ft_unset(cmd_struct->command, &env);
	else if (!path)
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
	if (!path_cmd)
	{
		ft_fprintf(STDERR_FILENO, "mishelle: command not found: `%s'\n", cmd);
	}
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
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		return;
	pid = fork();
	if (pid == -1)
		return;
	if (pid == 0)
	{
		redirect(cmd_struct, 0);
		redirect(cmd_struct, 1);
		close(fd[0]);
		if (!cmd_struct->file_out)
			dup2(fd[1], STDOUT_FILENO);
		execute_cmd(env, cmd_struct);
	}
	else
	{
		signal(SIGINT, parent_sig_handler);
		signal(SIGQUIT, parent_sig_handler);
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	redirect_out(char **file_out, char **type_out)
{
	int	i;
	int	fd_out;

	i = 0;
	if (!file_out || !type_out)
		return ;
	while (file_out[i])
	{
		if (type_out[i] && ft_strncmp(type_out[i], ">>", 3) == 0)
		{
			fd_out = open(file_out[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd_out, STDOUT_FILENO);
		}
		else if (type_out[i] && ft_strncmp(type_out[i], ">", 2) == 0)
		{
			fd_out = open(file_out[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd_out, STDOUT_FILENO);
		}
		i++;
	}
}

void	redirect(t_rinity *cmd_struct, int option)
{
	if (!option)
		redirect_in(cmd_struct->file_in, cmd_struct->type_in);
	else
		redirect_out(cmd_struct->file_out, cmd_struct->type_out);
}

void	redirect_in(char **file_in, char **type_in)
{
	int	i;
	int	fd_in;

	i = 0;
	if (!file_in || !type_in)
		return ;
	while (file_in[i])
	{
		if (type_in[i] && ft_strncmp(type_in[i], "<<", 3) == 0)
		{
			fd_in = ft_heredoc(file_in[i]);
			dup2(fd_in, STDIN_FILENO);
		}
		else if (type_in[i] && ft_strncmp(type_in[i], "<", 2) == 0)
		{
			fd_in = open(file_in[i], O_RDONLY);
			dup2(fd_in, STDIN_FILENO);
		}
		i++;
	}
}

/*void close_and_dup_fd(int *fd_in, int *fd_out, int *fd)
{
	if (*fd_in == -1)
		dup2(fd[0], STDIN_FILENO);
	if (*fd_in)
		dup2(*fd_in, STDIN_FILENO);
	if (*fd_out == -1)
		dup2(fd[1], STDOUT_FILENO);
	if (*fd_out)
		dup2(*fd_out, STDOUT_FILENO);
}*/

/*int create_fd_in(char **file_in, char **type_in)
{
	int	i;
	int	fd_in;

	i = 0;
	if (!file_in || !type_in)
		return (-1);
	while (file_in[i])
	{
		if (type_in[i] && ft_strncmp(type_in[i], "<<", 3) == 0)
			fd_in = ft_heredoc(file_in[i]);
		else if (type_in[i] && ft_strncmp(type_in[i], "<", 2) == 0)
			fd_in = open(file_in[i], O_RDONLY);
		i++;
	}
}*/

/*int create_fd_out(char **file_out, char **type_out)
{
	int	i;
	int	fd_out;

	i = 0;
	if (!file_out || !type_out)
		return (-1);
	while (file_out[i])
	{
		if (type_out[i] && ft_strncmp(type_out[i], ">>", 3) == 0)
			fd_out = append_file_out_content(file_out[i], 1);
		else if (type_out[i] && ft_strncmp(type_out[i], ">", 2) == 0)
			fd_out = append_file_out_content(file_out[i], 2);
		else
			return (-1);
		i++;
	}
	return (fd_out);
}*/

/*int append_file_out_content(char *file, int option)
{
	int file_fd;
	if (file)
	{
		if (option == 1)
			file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (option == 2)
			file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
		{
			ft_putstr_fd("mishelle: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
}*/

/*int append_file_content(char *file)
{
	int file_fd;
	if (file)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
		{
			ft_fprintf(STDERR_FILENO, "mishelle: `%s': No such file or directory\n");
			return (1);
		}
	}
	return (file_fd);
}*/


int	ft_heredoc(char *str)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-1);
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
			break;
		ft_fprintf(fd[1], "%s\n", line);
		free(line);
	}
	safe_free((void **)&line);
	close(fd[1]);
	return (fd[0]);
}
