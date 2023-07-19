/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:51:12 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/18 15:00:42 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*get_next_line(int fd)
{
	static t_gnl	*stack[1024];
	char			*line;

	line = NULL;
	if (fd < 0 || read(fd, &line, 0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	ft_read_stack(&stack[fd], fd);
	if (!stack[fd])
		return (NULL);
	extract_line(stack[fd], &line);
	clean_stack(&stack[fd]);
	if (line[0] == 0)
	{
		free_stack(stack[fd]);
		stack[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_read_stack(t_gnl **stack, int fd)
{
	char	*buffer;
	int		r_read;

	r_read = 1;
	while (!chearch_endline(*stack) && r_read != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		r_read = read(fd, buffer, BUFFER_SIZE);
		if ((!*stack && r_read == 0) || r_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[r_read] = 0;
		go_to_stack(stack, buffer, r_read);
		free(buffer);
	}
}

int	chearch_endline(t_gnl *stack)
{
	int		i;
	t_gnl	*last;

	if (!stack)
		return (0);
	last = lst_getlast(stack);
	i = 0;
	while (last->content[i])
	{
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_gnl	*lst_getlast(t_gnl *stack)
{
	t_gnl	*temp;

	temp = stack;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	go_to_stack(t_gnl **stack, char *buffer, int r_read)
{
	int		cnt;
	t_gnl	*temp;
	t_gnl	*last;

	cnt = 0;
	temp = malloc(sizeof(t_gnl));
	if (!temp)
		return ;
	temp->next = NULL;
	temp->content = malloc(sizeof(char) * (r_read + 1));
	if (!temp->content)
		return ;
	while (buffer[cnt] && cnt < r_read)
	{
		temp->content[cnt] = buffer[cnt];
		cnt++;
	}
	temp->content[cnt] = 0;
	if (!*stack)
	{
		*stack = temp;
		return ;
	}
	last = lst_getlast(*stack);
	last->next = temp;
}
