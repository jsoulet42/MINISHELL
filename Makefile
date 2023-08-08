# **************************************************************************** #
#    MINISHELL MAKEFILE                                                        #
# **************************************************************************** #

# Files variables ***************** #
NAME		=	minishell

ECHO_NAME	=	echo
ENV_NAME	=	env
PWD_NAME	=	pwd

VPATH		=	Srcs:			\
				Srcs/builtins:

SRCS		=	main.c					\
				parsing_01.c			\
				parsing_02.c			\
				parsing_03.c			\
				parsing_04.c			\
				parsing_05.c			\
				parsing_06.c			\
				parsing_07.c			\
				parsing_08.c			\
				doublquote_01.c			\
				simplquote_01.c			\
				display_01.c			\
				init_environment_01.c	\
				environment_utils_01.c	\
				environment_utils_02.c	\
				environment_utils_03.c	\
				free_utils_01.c			\
				utils_01.c				\
				check_starterrors01.c	\
				check_starterrors02.c	\
				interpret_01.c				\
				interpret_02.c			\
				interpret_03.c			\
				interpret_04.c			\
				ft_export.c				\
				get_next_line_bonus.c	\
				get_next_line_utils_bonus.c \
				lentab.c				\
				ft_cd.c					\
				ft_unset.c				\
				ft_exit.c				\
				ft_echo_01.c				\
				ft_pwd.c				\
				ft_env.c				\
				modif_shlvl.c			\
				signals.c

BUILTINS_DIR=	Srcs/builtins

BIN_DIR		=	bin

OBJS_DIR	=	Objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))


# Compilation variables *********** #
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

INCL_DIR	=	Includes

LIBS_DIR	=	Libs
LIBS		=	-lft -lncurses -lreadline

DEFINES		=	-D_GNU_SOURCE

# Files management variables ****** #
RM			=	rm -rf

# Display variables *************** #
ifndef $(SLEEP)
SLEEP		=	0
endif
ifndef $(SCREEN_W)
SCREEN_W	=	70
endif
ifndef $(SCREEN_H)
SCREEN_H	=	40
endif

# **************************************************************************** #

all:	screen builtins $(NAME)

# Compilation rules *************** #
$(NAME):	screen $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS)  $(DEFINES) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	@$(call terminal_disp, "Compiled executable: '$@'")

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled object file: '$@'")

$(OBJS_DIR): screen
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 0)
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp, "Created objects directory '$(OBJS_DIR)/'")
endif

$(BIN_DIR): screen
ifeq ($(shell if [ -d "$(BIN_DIR)" ]; then echo 1; else echo 0; fi), 0)
	@mkdir $(BIN_DIR)
	@$(call terminal_disp, "Created binaries directory '$(BIN_DIR)/'")
endif

# File management rules *********** #
clean: screen
ifneq ($(shell ls $(OBJS_DIR)/*.o 2> /dev/null | wc -l), 0)
	@$(RM) $(OBJS_DIR)/*.o
	@$(call terminal_disp, "Removed object files")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(OBJS_DIR)/*.o'")
endif

fclean:	screen clean
ifeq ($(shell if [ -f "$(NAME)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(NAME);
	@$(call terminal_disp, "Removed executable file")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(NAME)'")
endif

binclean: screen clean
ifneq ($(shell ls $(BIN_DIR) 2> /dev/null | wc -l), 0)
	@$(RM) $(BIN_DIR)/*
	@$(call terminal_disp, "Removed builtin executable files")
else
	@$(call terminal_disp, "make: Nothing to be done for '$(RM) $(BIN_DIR)/*'")
endif

dclean:	screen binclean
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

binre: screen binclean builtins

minishellre: screen fclean $(NAME)

re:	screen binclean fclean all

# Display rules ******************* #
screen:
ifdef $(YES)
	@clear
	@$(call put_screen)
endif

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
		sleep $(SLEEP);											\
	done;														\
	echo
endef

define put_screen
	$(call put_screen_width)
	$(call put_screen_height)
	$(call put_screen_width)
endef

define put_screen_width
	@echo -n "/";							\
	i=1;									\
	while [ $${i} -lt $$(( $(SCREEN_W) - 1 )) ]; do		\
		echo -n "=";		\
		i=$$(expr $$i + 1);										\
	done;		\
	echo "\\"
endef

# **************************************************************************** #

.PHONY:	all builtins clean fclean binclean dclean binre re screen
