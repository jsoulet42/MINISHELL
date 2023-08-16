/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/16 18:57:30 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

void	redirect_in(char **file_in, char **type_in)
{
	int	i;
	int	fd_in;

	if (!file_in || !type_in)
		return ;
	i = -1;
	while (file_in[++i])
	{
		if (type_in[i] && ft_strncmp(type_in[i], "<<", 3) == 0)
		{
			fd_in = ft_heredoc(file_in[i]);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			unlink("./.heredoc");
		}
		if (type_in[i] && ft_strncmp(type_in[i], "<", 2) == 0)
		{
			fd_in = open(file_in[i], O_RDONLY);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
}

void	redirect_streams(t_rinity *cmd_struct)
{
	redirect_in(cmd_struct->file_in, cmd_struct->type_in);
	redirect_out(cmd_struct->file_out, cmd_struct->type_out);
}

int	ft_heredoc(char *str)
{
	int		len;
	int		heredoc_fd;
	char	*line;
	char	*line_temp;

	len = ft_strlen(str);
	line_temp = NULL;
	heredoc_fd = open("./.heredoc" , O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_fprintf(STDIN_FILENO, "\e[2J");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, str, len + 1) == 0)
			break ;
		line_temp = expand_dollars(line, g_shell_data->env);
		free(line);
		ft_fprintf(heredoc_fd, "%s\n", line_temp);
	}
	safe_free((void **)&line_temp);
	close(heredoc_fd);
	heredoc_fd = open("./.heredoc" , O_CREAT | O_RDONLY, 0644);
	return (heredoc_fd);
}
