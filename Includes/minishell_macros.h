/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:31:05 by mdiamant          #+#    #+#             */
/*   Updated: 2023/07/13 10:46:51 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MACROS_H
# define MINISHELL_MACROS_H

# define OPERANDS_COUNT 12

# define OPERANDS "| || & && $ $$ < > \\ ' \" << >>"

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

#endif
