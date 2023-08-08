/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:16:19 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 17:55:22 by jsoulet          ###   ########.fr       */
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

int	ft_heredoc(char *str)
{
	char	*line;
	char	*line_temp;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-1);
		if (ft_strncmp(line, str, ft_strlen(str)) == 0
			&& ft_strlen(line) == ft_strlen(str))
			break ;
		line_temp = expand_dollars(line, g_shell_data->env);
		free(line);
		ft_fprintf(fd[1], "%s\n", line_temp);
	}
	safe_free((void **)&line_temp);
	close(fd[1]);
	return (fd[0]);
}
