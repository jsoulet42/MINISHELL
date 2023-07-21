/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:51:49 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/21 15:00:50 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
void	ft_read_stack(t_gnl **stack, int fd);
void	go_to_stack(t_gnl **stack, char *buffer, int r_read);
void	extract_line(t_gnl *stack, char **line);
t_gnl	*lst_getlast(t_gnl *stack);
int		chearch_endline(t_gnl *stack);
void	generate_line(char **line, t_gnl *stack);
void	free_stack(t_gnl *stack);
int		ft_strgnl(const char *s);
void	clean_stack(t_gnl **stack);

#endif
