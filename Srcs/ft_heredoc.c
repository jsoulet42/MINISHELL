/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:22:15 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/28 00:02:22 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	heredoc_write(char *stop, int *fd)
{
	int		len;
	char	*line;
	char	*temp;

	len = ft_strlen(stop);
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
		temp = expand_cmd(line, SH_UNBOUND, g_shell_data->env);
		free(line);
		if (!temp)
			return ;
		ft_fprintf(fd[1], "%s\n", temp);
		free(temp);
	}
	if (line)
		free(line);
}

static int	herefork(pid_t pid, char *stop, int *fd)
{
	int		status_code;

	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		heredoc_write(stop, fd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_sig_handler);
		close(fd[1]);
		waitpid(pid, &status_code, 0);
		get_exit_code(status_code, &g_shell_data->exit_code);
	}
	return (status_code);
}

int	ft_heredoc(char *str)
{
	int		fd[2];
	pid_t	pid;

	dup2(g_shell_data->in, STDIN_FILENO);
	if (pipe(fd) == -1)
	{
		perror("mishelle: here-document");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror("mishelle: here-document");
		return (-1);
	}
	if (herefork(pid, str, fd))
		return (close(fd[0]), -1);
	return (fd[0]);
}
