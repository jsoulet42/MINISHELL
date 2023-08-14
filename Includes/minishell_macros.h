/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:25 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/14 20:44:55 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MACROS_H
# define MINISHELL_MACROS_H

# define OPERANDS_COUNT 12
# define OPERANDS "| || & && < > \\ ' \" << >>"
# define PIPE "|"
# define AND "&&"
# define OR "||"
# define DOL "$"
# define DOL_DOL "$$"
# define REDIR_IN "<"
# define REDIR_OUT ">"
# define REDIR_APPEND ">>"
# define REDIR_HERE_DOC "<<"
# define BACKSLASH "\\"
# define SIMPLE_QUOTE "'"
# define DOUBLE_QUOTE "\""

/* Status codes for function returns */
# define SH_SUCCESS	0
# define SH_ERROR	1

/* Prompt string buffer size */
# define PROMPT_BUFFER	255

/* Startup environment variables */
# define START_LOGNAME	"LOGNAME=guest"
# define START_NAME		"NAME=mishelle"
# define START_PWD		"PWD="
# define START_OLDPWD	"OLDPWD="
# define START_SHLVL	"SHLVL=2"

/* Environment variable update modes */
# define SH_OVERWRITE	0
# define SH_ADDBACK		1
# define SH_ADDFRONT	2

/* Environment display mode */
# define SH_DISORDERED	0
# define SH_ORDERED		1

/* Termios setup modes */
# define TERMIOS_UNMUTE_CTRL	0
# define TERMIOS_MUTE_CTRL		1

#endif
