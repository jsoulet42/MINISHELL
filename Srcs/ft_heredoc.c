/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:22:15 by hnogared          #+#    #+#             */
/*   Updated: 2023/08/26 18:09:52 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	heredoc_write(char *stop, int *fd)
{
	int		len;
	char	*line;
	char	*line_temp;

	close(fd[0]);
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
		ft_fprintf(fd[1], "%s\n", line_temp);
	}
	safe_free((void **)&line_temp);
	close(fd[1]);
	exit(0);
}

int	ft_heredoc(char *str)
{
	int		status_code;
	int		fd[2];
	pid_t	pid;

	dup2(g_shell_data->in, STDIN_FILENO);
	if (pipe(fd) == -1)
		return (perror("mishelle: here-document"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("mishelle: here-document"), -1);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		heredoc_write(str, fd);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_sig_handler);
		close(fd[1]);
		waitpid(pid, &status_code, 0);
		get_exit_code(status_code, &g_shell_data->exit_code);
	}
	if (g_shell_data->exit_code)
		return (close(fd[0]), -1);
	return (fd[0]);
}
