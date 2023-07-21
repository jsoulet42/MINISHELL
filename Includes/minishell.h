/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:19:05 by hnogared          #+#    #+#             */
/*   Updated: 2023/07/20 17:36:43 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

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

typedef struct s_parsing t_par;
typedef struct s_env t_env;
typedef struct s_par t_rinity;

typedef struct s_shell
{
	t_par		**par;
	t_env		*env;
	t_rinity	**t;
	char		**commande;
	int 		in;
	int 		out;
	int 		fd[2];
}				t_shell;

extern t_shell *g_shell_data;

# include "mdiamant.h"
# include "hnogared.h"
# include "lolefevr.h"
# include "jsoulet.h"
# include "hnogared.h"


/*-----------------Srcs/lolefevr/doublquote_01.c-----------------*/
int		doublquote(char *str);

/*-----------------Srcs/lolefevr/simplquote_01.c-----------------*/
int		simplquote(char *str);

#endif
