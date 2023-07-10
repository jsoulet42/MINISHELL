# **************************************************************************** #
#    MINISHELL MAKEFILE                                                        #
# **************************************************************************** #

NAME		=	minishell

VPATH		=	Srcs:		\

SRCS		=	main.c

OBJS_DIR	=	Objs
OBJS		=	$(SRCS:.c=.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

INCL_DIR	=	Includes

LIBS_DIR	=	Libs
LIBS		=	-lft

RM			= rm -rf


all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -L $(LIBS_DIR) $(LIBS) $(OBJS) -o $@

$(OBJS_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -L $(LIBS_DIR) $(LIBS) -c $< -o $@

$(OBJS_DIR):
	@if [ ! -d $(OBJS_DIR) ]; then							\
		mkdir $(OBJS_DIR);									\
		echo "Created objects directory '$(OBJS_DIR)/'";	\
	fi

clean:
	@if [ ls *.flac >/dev/null  2>&1 ]; then					\
		$(RM) $(OBJS_DIR)/*.o;									\
		echo "Removed all object files";						\
	else														\
		echo "Nothing to be done for: $(RM) $(OBJS_DIR)/*.o";	\
	fi

fclean:	clean
	@if [ ls *.flac >/dev/null  2>&1 ]; then			\
		$(RM) $(NAME);									\
		echo "Removed executable file";					\
	else												\
		echo "Nothing to be done for: $(RM) $(NAME)";	\
	fi

dclean:	clean
	@if [ -d $(OBJS_DIR) ]; then							\
		$(RM) $(OBJS_DIR);									\
		echo "Removed objects directory '$(OBJS_DIR)/'";	\
	else													\
		echo "Nothing to be done for: $(RM) $(OBJS_DIR)";	\
	fi

re:	fclean all

.PHONY:	all clean fclean dclean re
