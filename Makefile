# **************************************************************************** #
#    MINISHELL MAKEFILE                                                        #
# **************************************************************************** #

# Files variables ***************** #
NAME		=	minishell

VPATH		=	Srcs:		\
				Srcs/mdiamant:


SRCS		=	main.c\
				parsing_01.c\
				error_exit_01.c

OBJS_DIR	=	Objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# Compilation variables *********** #
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

INCL_DIR	=	Includes

LIBS_DIR	=	Libs
LIBS		=	-lft

# Files management variables ****** #
RM			=	rm -rf

# **************************************************************************** #

all:	$(NAME)

# Compilation rules *************** #
$(NAME):	$(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled executabl: $@")

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled object file: $@")

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp, "Created objects directory \'$(OBJS_DIR)/\'")

# File management rules *********** #
clean:
ifneq ($(shell ls $(OBJS_DIR)/*.o 2> /dev/null | wc -l), 0)
	@$(RM) $(OBJS_DIR)/*.o
	@$(call terminal_disp, "Removed object files")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(OBJS_DIR)/*.o'")
endif

fclean:	clean
ifeq ($(shell if [ -f "$(NAME)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(NAME);
	@$(call terminal_disp, "Removed executable file")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(NAME)'")
endif

dclean:	clean
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(OBJS_DIR)
	@$(call terminal_disp, "Removed objects directory '$(OBJS_DIR)/'")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(OBJS_DIR)'")
endif

re:	fclean all

# **************************************************************************** #

# Display functions *************** #
define terminal_disp
	$(eval message = $(1))
	echo "$$> ${message}"
endef

# **************************************************************************** #

.PHONY:	all clean fclean dclean re
