# **************************************************************************** #
#    MINISHELL MAKEFILE                                                        #
# **************************************************************************** #

# Files variables ***************** #
NAME		=	minishell

ECHO_NAME	=	echo
ENV_NAME	=	env
PWD_NAME	=	pwd
CD_NAME		=	cd

VPATH		=	Srcs:			\
				Srcs/builtins:	\
				Srcs/mdiamant:	\
				Srcs/lolefevr:	\
				Srcs/hnogared:	\
				Srcs/jsoulet

SRCS		=	main.c					\
				parsing_01.c			\
				error_exit_01.c			\
				doublquote_01.c			\
				simplquote_01.c			\
				display_01.c			\
				init_environment_01.c	\
				environment_utils_01.c	\
				environment_utils_02.c	\
				utils_01.c				\
				check_starterrors01.c	\
				check_starterrors02.c	\
				interpret.c				\
				ft_export.c				\
				ft_unset.c

BUILTINS_DIR=	Srcs/builtins
ECHO_SRCS	=	ft_echo_01.c
ENV_SRCS	=	ft_env.c
PWD_SRCS	=	ft_pwd.c
CD_SRCS		=	ft_cd.c

BIN_DIR		=	bin
ECHO_BIN	=	$(addprefix $(BIN_DIR)/, $(ECHO_NAME))
ENV_BIN		=	$(addprefix $(BIN_DIR)/, $(ENV_NAME))
PWD_BIN		=	$(addprefix $(BIN_DIR)/, $(PWD_NAME))
CD_BIN		=	$(addprefix $(BIN_DIR)/, $(CD_NAME))

OBJS_DIR	=	Objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
ECHO_OBJS	=	$(addprefix $(OBJS_DIR)/, $(ECHO_SRCS:.c=.o))
ENV_OBJS	=	$(addprefix $(OBJS_DIR)/, $(ENV_SRCS:.c=.o))
PWD_OBJS	=	$(addprefix $(OBJS_DIR)/, $(PWD_SRCS:.c=.o))
CD_OBJS		=	$(addprefix $(OBJS_DIR)/, $(CD_SRCS:.c=.o))

# Compilation variables *********** #
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

INCL_DIR	=	Includes

LIBS_DIR	=	Libs
LIBS		=	-lft -lncurses -lreadline

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
	@$(CC) $(CFLAGS) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	@$(call terminal_disp, "Compiled executable: '$@'")

builtins:	screen $(ECHO_BIN) $(ENV_BIN) $(PWD_BIN) $(CD_BIN)

$(ECHO_NAME):	$(ECHO_BIN)

$(ENV_NAME):	$(ENV_BIN)

$(PWD_NAME):	$(PWD_BIN)

$(CD_NAME):		$(CD_BIN)

$(ECHO_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(ECHO_OBJS)
	@$(CC) $(CFLAGS) $(ECHO_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(ECHO_NAME)'")

$(ENV_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(ENV_OBJS)
	@$(CC) $(CFLAGS) $(ECHO_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(ENV_NAME)'")

$(PWD_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(PWD_OBJS)
	@$(CC) $(CFLAGS) $(PWD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(PWD_NAME)'")

$(CD_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(CD_OBJS)
	@$(CC) $(CFLAGS) $(CD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(CD_NAME)'")

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
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
