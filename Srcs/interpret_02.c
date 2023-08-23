/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/23 12:55:15 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	heredoc_write(char *stop, int fd)
{
	int		len;
	char	*line;
	char	*line_temp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	len = ft_strlen(stop);
	line_temp = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("mishelle: warning: ");
			ft_printf("here-document delimited by EOF (wanted `%s')\n", stop);
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

int	ft_heredoc(char *str)
{
	int		fd[2];
	pid_t	pid;

	dup2(g_shell_data->in, STDIN_FILENO);
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (perror("mishelle: here-document"), -1);
	else if (pid == 0)
	{
		close(fd[0]);
		heredoc_write(str, fd[1]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, parent_sig_handler);
		close(fd[1]);
		waitpid(pid, &g_shell_data->exit_code, 0);
	}
	if (g_shell_data->exit_code)
		return (close(fd[0]), -1);
	return (fd[0]);
}

int	redirect_in(char **file_in, char **type_in)
{
	int	i;
	int	fd_in;

	if (!file_in || !type_in)
		return (SH_SUCCESS);
	i = -1;
	errno = 0;
	while (file_in[i + 1] && type_in[i + 1])
	{
		i++;
		fd_in = -1;
		if (ft_strncmp(type_in[i], "<<", 3) == 0)
		{
			fd_in = ft_heredoc(file_in[i]);
			if (fd_in < 0)
				return (SH_ERROR);
		}
		if (errno == 0 && ft_strncmp(type_in[i], "<", 2) == 0)
			fd_in = open(file_in[i], O_RDONLY, 0644);
		if (fd_in < 0)
			continue ;
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (errno)
		perror("mishelle");
	return (errno);
}

int	redirect_out(char **file_out, char **type_out)
{
	int	i;
	int	fd_out;

	if (!file_out || !type_out)
		return (SH_SUCCESS);
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
			break ;
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		fd_out = -1;
	}
	return (errno);
}

int	redirect_streams(t_rinity *cmd_struct)
{
	int	status_code;

	status_code = redirect_in(cmd_struct->file_in, cmd_struct->type_in);
	if (status_code)
		return (status_code);
	return (redirect_out(cmd_struct->file_out, cmd_struct->type_out));
}
