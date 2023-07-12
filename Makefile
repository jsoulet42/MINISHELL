# **************************************************************************** #
#    MINISHELL MAKEFILE                                                        #
# **************************************************************************** #

# Files variables ***************** #
NAME		=	minishell

BIN_DIR		=	bin
ECHO_NAME	=	echo
ECHO_PATH	=	$(addprefix $(BIN_DIR)/, $(ECHO_NAME))

VPATH		=	Srcs:			\
				Srcs/builtins:	\
				Srcs/mdiamant:	\
				Srcs/lolefevr:	\
				Srcs/hnogared:

SRCS		=	main.c			\
				parsing_01.c	\
				error_exit_01.c	\
				doublquote_01.c	\
				simplquote_01.c	\
				main_hnogared.c

ECHO_SRCS	=	ft_echo_01.c

OBJS_DIR	=	Objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
ECHO_OBJS	=	$(addprefix $(OBJS_DIR)/, $(ECHO_SRCS:.c=.o))

# Compilation variables *********** #
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

INCL_DIR	=	Includes

LIBS_DIR	=	Libs
LIBS		=	-lft -lncurses -lreadline

# Files management variables ****** #
RM			=	rm -rf

# **************************************************************************** #

all:	$(NAME)

# Compilation rules *************** #
$(NAME):	$(ECHO_PATH) $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	@$(call terminal_disp, "Compiled executable: '$@'")

$(ECHO_NAME):	$(ECHO_PATH)

$(ECHO_PATH):	$(BIN_DIR) $(OBJS_DIR) $(ECHO_OBJS)
	@$(CC) $(CFLAGS) $(ECHO_OBJS) -L $(LIBS_DIR) $(LIBS) -o $(ECHO_PATH) $(LDLIBS)
	@$(call terminal_disp, "Compiled builtin binary: '$@'")

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled object file: '$@'")

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp, "Created objects directory '$(OBJS_DIR)/'")

$(BIN_DIR):
	@mkdir $(BIN_DIR)
	@$(call terminal_disp, "Created binaries directory '$(BIN_DIR)/'")

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

binclean: clean
ifeq ($(shell if [ -f "$(ECHO_PATH)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(ECHO_PATH);
	@$(call terminal_disp, "Removed builtin executable file: '$(ECHO_NAME)'")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(ECHO_PATH)'")
endif

dclean:	binclean
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(OBJS_DIR)
	@$(call terminal_disp, "Removed objects directory '$(OBJS_DIR)/'")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(OBJS_DIR)'")
endif
ifeq ($(shell if [ -d "$(BIN_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(BIN_DIR)
	@$(call terminal_disp, "Removed objects directory '$(BIN_DIR)/'")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(BIN_DIR)'")
endif

re:	fclean all

# **************************************************************************** #

# Display functions *************** #
define terminal_disp
	$(eval message = $(1))
	@sh_message=$(message);										\
	i=1;														\
	echo -n "makefile@minishell $$> ";							\
	while [ $${i} -le $${#sh_message} ]; do						\
		echo -n "$$(echo $${sh_message} | cut -c $${i}-$${i})";	\
		i=$$(expr $$i + 1);										\
	done;														\
	echo
endef

#echo "$$> ${message}"
# **************************************************************************** #

.PHONY:	all clean fclean binclean dclean re
