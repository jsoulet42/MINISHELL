/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:21:22 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 17:40:22 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_strgnl(const char *src)
{
	int	len;

	len = 0;
	while (*src++)
		len++;
	return (len);
}

void	generate_line(char **line, t_gnl *stack)
{
	int	i;
	int	len;

	len = 0;
	while (stack)
	{
		i = 0;
		while (stack->content[i])
		{
			if (stack->content[i] == '\n')
			{
				len++;
				break ;
			}
			i++;
			len++;
		}
		stack = stack->next;
	}
	*line = malloc(sizeof(char) * (len +1));
}

void	free_stack(t_gnl *stack)
{
	t_gnl	*new_temp;
	t_gnl	*next;

	new_temp = stack;
	while (new_temp)
	{
		free(new_temp->content);
		next = new_temp->next;
		free(new_temp);
		new_temp = next;
	}
}

void	clean_stack(t_gnl **stack)
{
	t_gnl	*temp;
	t_gnl	*last;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(t_gnl));
	if (!stack || !temp)
		return ;
	temp->next = NULL;
	last = lst_getlast(*stack);
	while (last->content[i] != '\n' && last->content[i])
		i++;
	if (last->content[i] == '\n')
		i++;
	temp->content = malloc(sizeof(char) * (ft_strgnl(last->content + i) + 1));
	if (!temp->content)
		return ;
	while (last->content[i] != '\0')
		temp->content[j++] = last->content[i++];
	temp->content[j] = 0;
	free_stack(*stack);
	*stack = temp;
}

void	extract_line(t_gnl *stack, char **line)
{
	int		i;
	int		j;

	j = 0;
	if (!stack)
		return ;
	generate_line(line, stack);
	if (!*line)
		return ;
	while (stack)
	{
		i = 0;
		while (stack->content[i])
		{
			if (stack->content[i] == '\n')
			{
				(*line)[j++] = stack->content[i];
				break ;
			}
			(*line)[j++] = stack->content[i++];
		}
		stack = stack->next;
	}
	(*line)[j] = 0;
}
