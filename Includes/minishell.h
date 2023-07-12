/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:19:05 by hnogared          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/12 12:12:33 by lolefevr         ###   ########.fr       */
=======
/*   Updated: 2023/07/12 17:31:51 by hnogared         ###   ########.fr       */
>>>>>>> 1f19e556878f8bcef6d11284a9f6a56f21cdc6dc
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

<<<<<<< HEAD
//#include <readline> //FLAG: -lreadline*****readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history		*****
#include <stdio.h> //					*****printf																						*****
#include <stdlib.h> //					*****malloc free exit																			*****
#include <unistd.h> //					*****write, access, open, read, close, fork, execve, dup, dup2, pipe, isatty, unlink			*****
#include <sys/wait.h> //				*****wait, waitpid, wait3, wait4																*****
#include <signal.h> //					*****signal, sigaction, sigemptyset, sigaddset, kill											*****
#include <sys/stat.h> //				*****stat, lstat, fstat																			*****
#include <dirent.h> //					*****opendir, readdir, closedir																	*****
#include <string.h> //					*****steerror, strerror_r																		*****
#include <sys/types.h> //				*****pid_t																						*****
#include <termios.h> //					*****tcsetattr, tcgetattr																		*****
//#include <curses.h> //FLAG: -lncurses	*****tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs											*****
#include <errno.h> //					*****errno																						*****
//#include <term.h> //					*****tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs											*****
=======
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

# include "hnogared.h"
# include "mdiamant.h"
# include "lolefevr.h"
# include "jsoulet.h"
>>>>>>> 1f19e556878f8bcef6d11284a9f6a56f21cdc6dc


typedef struct s_parsing
{
	char	*str;
	int		type; //0 = string, 1 = operand, 2 = option, 3 = variable, 4 = num
}				t_par;


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
