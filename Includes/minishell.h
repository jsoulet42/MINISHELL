#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <errno.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <termios.h>
# include <curses.h>
# include <errno.h>
# include <term.h>

# include "minishell_macros.h"

typedef struct s_parsing t_par;
typedef struct s_env t_env;
typedef struct s_par t_rinity;

typedef struct s_shell
{
	t_par		**par;
	t_env		*env;
	t_rinity	**t;
	int 		in;
	int 		out;
	int 		fd[2];
	char		*path;
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

void	print_str_tab(char **str_tab);


#endif
