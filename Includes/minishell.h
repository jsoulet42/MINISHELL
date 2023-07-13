/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:19:05 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/12 17:57:16 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <readline/readline.h> //FLAG: -lreadline*****readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history		*****
# include <stdio.h> //					*****printf																						*****
# include <stdlib.h> //					*****malloc free exit																			*****
# include <unistd.h> //					*****write, access, open, read, close, fork, execve, dup, dup2, pipe, isatty, unlink			*****
# include <sys/wait.h> //				*****wait, waitpid, wait3, wait4																*****
# include <signal.h> //					*****signal, sigaction, sigemptyset, sigaddset, kill											*****
# include <sys/stat.h> //				*****stat, lstat, fstat																			*****
# include <dirent.h> //					*****opendir, readdir, closedir																	*****
# include <string.h> //					*****steerror, strerror_r																		*****
# include <sys/types.h> //				*****pid_t																						*****
# include <termios.h> //					*****tcsetattr, tcgetattr																		*****
# include <curses.h> //FLAG: -lncurses	*****tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs											*****
# include <errno.h> //					*****errno																						*****
# include <term.h> //					*****tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs											*****

# include "minishell_macros.h"

# include "mdiamant.h"
# include "lolefevr.h"
# include "jsoulet.h"
# include "hnogared.h"

/*-----------------Srcs/mdiamant/parsing_01.c-----------------*/
int		is_operand(const char *str);
t_par	**init_parsing(char *argv);
int		count_arg(const char *argv);
void	ft_parsing(char *argv);
int		getSkipCount(const char *str);

/*-----------------Srcs/mdiamant/error_exit_01.c-----------------*/
void	error_exit(char *str);

/*-----------------Srcs/lolefevr/doublquote_01.c-----------------*/
int		doublquote(char *str);

/*-----------------Srcs/lolefevr/simplquote_01.c-----------------*/
int		simplquote(char *str);

#endif
