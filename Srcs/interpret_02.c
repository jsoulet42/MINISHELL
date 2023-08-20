/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/20 18:32:40 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	heredoc_read_write(char *stop, int fd)
{
	int		len;
	char	*line;
	char	*line_temp;

	len = ft_strlen(stop);
	line_temp = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("mishelle: warning: ");
			ft_printf("heredoc delimited by end-of-file (wanted `%s')\n", stop);
			break ;
		}
		if (ft_strncmp(line, stop, len + 1) == 0)
			break ;
		line_temp = expand_dollars(line, g_shell_data->env);
		free(line);
		ft_fprintf(fd, "%s\n", line_temp);
	}
	safe_free((void **)&line_temp);
}

		//tmp = open("test", O_CREAT | O_WRONLY, 0644);

int	ft_heredoc(char *str)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		dup2(STDIN_FILENO, fd[0]);
		heredoc_read_write(str, STDIN_FILENO);
		close(fd[1]);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(fd[1], STDIN_FILENO);
		close(fd[0]);
	}
	return (STDIN_FILENO);
}

void	redirect_out(char **file_out, char **type_out)
{
	int	i;
	int	fd_out;

	if (!file_out || !type_out)
		return ;
	fd_out = -1;
	i = -1;
	while (file_out[++i])
	{
		if (type_out[i] && ft_strncmp(type_out[i], ">>", 3) == 0)
			fd_out = open(file_out[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (type_out[i] && ft_strncmp(type_out[i], ">", 2) == 0)
			fd_out = open(file_out[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("mishelle");
			continue ;
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		fd_out = -1;
	}
}

void	redirect_in(char **file_in, char **type_in)
{
	int	i;
	int	fd_in;

	if (!file_in || !type_in)
		return ;
	fd_in = -1;
	i = -1;
	while (file_in[++i])
	{
		if (type_in[i] && ft_strncmp(type_in[i], "<<", 3) == 0)
			fd_in = ft_heredoc(file_in[i]);
		if (type_in[i] && ft_strncmp(type_in[i], "<", 2) == 0)
			fd_in = open(file_in[i], O_RDONLY, 0644);
		if (fd_in < 0)
		{
			perror("mishelle");
			continue ;
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

void	redirect_streams(t_rinity *cmd_struct)
{
	redirect_in(cmd_struct->file_in, cmd_struct->type_in);
	redirect_out(cmd_struct->file_out, cmd_struct->type_out);
}
