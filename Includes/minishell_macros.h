/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:07:25 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/07 13:07:26 by jsoulet          ###   ########.fr       */
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

#endif
