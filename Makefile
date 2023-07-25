# **************************************************************************** #
#                                                                              #
#    MINISHELL MAKEFILE                                                        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    Variables                                                                 #
# **************************************************************************** #
# Files variables ************************************************************ #

## Executable name
NAME		=	minishell

## Builtins names
ECHO_NAME	=	echo
ENV_NAME	=	env
PWD_NAME	=	pwd
CD_NAME		=	cd

## Paths to all source files
VPATH		=	Srcs:			\
				Srcs/builtins:	\
				Srcs/mdiamant:	\
				Srcs/lolefevr:	\
				Srcs/hnogared:	\
				Srcs/jsoulet

## Source files names
SRCS		=	main.c						\
				parsing_01.c				\
				error_exit_01.c				\
				doublquote_01.c				\
				simplquote_01.c				\
				display_01.c				\
				init_environment_01.c		\
				environment_utils_01.c		\
				environment_utils_02.c		\
				environment_utils_03.c		\
				free_utils_01.c				\
				utils_01.c					\
				check_starterrors01.c		\
				check_starterrors02.c		\
				interpret.c					\
				ft_export.c					\
				get_next_line_bonus.c		\
				get_next_line_utils_bonus.c	\
				signals.c

## Builtins sources directory
BUILTINS_DIR=	Srcs/builtins
## Builtins source names
ECHO_SRCS	=	ft_echo_01.c
ENV_SRCS	=	ft_env.c
PWD_SRCS	=	ft_pwd.c
CD_SRCS		=	ft_cd.c

## Builtins binaries directory
BIN_DIR		=	bin
## Builtins binaries names
ECHO_BIN	=	$(addprefix $(BIN_DIR)/, $(ECHO_NAME))
ENV_BIN		=	$(addprefix $(BIN_DIR)/, $(ENV_NAME))
PWD_BIN		=	$(addprefix $(BIN_DIR)/, $(PWD_NAME))
CD_BIN		=	$(addprefix $(BIN_DIR)/, $(CD_NAME))

## Object files directory
OBJS_DIR	=	Objs
## Object files names
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
ECHO_OBJS	=	$(addprefix $(OBJS_DIR)/, $(ECHO_SRCS:.c=.o))
ENV_OBJS	=	$(addprefix $(OBJS_DIR)/, $(ENV_SRCS:.c=.o))
PWD_OBJS	=	$(addprefix $(OBJS_DIR)/, $(PWD_SRCS:.c=.o))
CD_OBJS		=	$(addprefix $(OBJS_DIR)/, $(CD_SRCS:.c=.o))

# **************************************************************************** #
# Compilation variables ****************************************************** #

## Compilator
CC			=	gcc
## Compilation flags
CFLAGS		=	-Wall -Werror -Wextra

## Header files directory
INCL_DIR	=	Includes

## Libraries files directory
LIBS_DIR	=	Libs
## Libraries files names
LIBS		=	-lft -lncurses -lreadline

## Define macros
DEFINES		=	-D_GNU_SOURCE

# **************************************************************************** #
# File management variables ************************************************** #
RM			=	rm -rf

# **************************************************************************** #
# Display variables *************** #
ifndef $(SLEEP)
SLEEP		=	0
endif

ifndef $(SCREEN_W)
SCREEN_W	=	70
endif
ifndef $(SCREEN_H)
SCREEN_H	=	25
endif
ifndef $(FANCY)
FANCY		=	0
endif

SCREEN_R_OFFSET	=	20

SCREEN_BORDER	=	"╔" "═" "╗" "║" "╚" "═" "╝"

# **************************************************************************** #

all:	screen builtins $(NAME)

# Compilation rules *************** #
$(NAME):	screen $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS)  $(DEFINES) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
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
	@$(CC) $(CFLAGS) $(ENV_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(ENV_NAME)'")

$(PWD_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(PWD_OBJS)
	@$(CC) $(CFLAGS) $(PWD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(PWD_NAME)'")

$(CD_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(CD_OBJS)
	@$(CC) $(CFLAGS) $(CD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled builtin binary: '$(CD_NAME)'")

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
ifneq ($(FANCY), 0)
	@clear
	@$(call put_screen)
	@$(call put_keyboard)
	@echo -n "\e[s\e[3;4f"
endif

# **************************************************************************** #

# Display functions *************** #
define terminal_disp
	$(eval message = $(1))
	@sh_message=$(message);													\
	i=1;																	\
	echo -n "makefile@minishell $$> ";										\
	while [ $$i -le $${#sh_message} ]; do									\
		echo -n "$$(echo $${sh_message} | cut -c $${i}-$${i})";				\
		if [ $(FANCY) -ne 0 ] && [ $$i -eq $$(( $(SCREEN_W) - 24 )) ]; then	\
			echo -n "\n\e[3C";												\
		fi;																	\
		i=$$(expr $$i + 1);													\
		sleep $(SLEEP);														\
	done
	@echo
	@if [ $(FANCY) -ne 0 ]; then	\
		echo -n "\e[3C";			\
	fi
endef

define put_screen
	$(eval top_l = $(word 1, $(SCREEN_BORDER)))
	$(eval top = $(word 2, $(SCREEN_BORDER)))
	$(eval top_r = $(word 3, $(SCREEN_BORDER)))
	$(eval side = $(word 4, $(SCREEN_BORDER)))
	$(eval bot_l = $(word 5, $(SCREEN_BORDER)))
	$(eval bot = $(word 6, $(SCREEN_BORDER)))
	$(eval bot_r = $(word 7, $(SCREEN_BORDER)))
	$(call put_box_width, $(top_l), $(top), $(top_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET)))
	$(call put_vertical_line, $(side), $(shell expr $(SCREEN_H) + 2), 0)
	$(call put_vertical_line, $(side), $(shell expr $(SCREEN_H) + 2),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET) - 1))
	@echo -n "\e[2C"
	$(call put_box_width, $(top_l), $(top), $(top_r), $(SCREEN_W))
	$(call put_vertical_line, $(side), $(SCREEN_H), 2)
	$(call put_vertical_line, $(side), $(SCREEN_H),	$(shell expr $(SCREEN_W) + 1))
	$(call put_vertical_line, $(side), $(SCREEN_H),	$(shell expr $(SCREEN_W) + 1))
	@echo -n "\e[$(SCREEN_H)B\e[2C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r), $(SCREEN_W))
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET)))
endef

define put_keyboard
	$(call put_box_width, $(top_l), $(top), $(top_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET)))
	$(call put_vertical_line, $(side), 3, 0)
	$(call put_vertical_line, $(side), 3,	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET) - 1))
	@echo -n "\e[3B"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET)))
endef

define put_box_width
	$(eval left_char = $(1))
	$(eval mid_char = $(2))
	$(eval right_char = $(3))
	$(eval width = $(4))
	@echo -n "$(left_char)";					\
	i=1;										\
	while [ $$i -lt $$(( $(width) - 1 )) ]; do	\
		echo -n "$(mid_char)";					\
		i=$$(expr $$i + 1);						\
	done
	@echo "$(right_char)"
endef

define put_vertical_line
	$(eval border = $(1))
	$(eval height = $(2))
	$(eval r_offset = $(3))
	@i=0;								\
	while [ $$i -lt $(height) ]; do		\
		if [ $(r_offset) -gt 0 ]; then	\
			echo -n "\e[$(r_offset)C";	\
		fi;								\
		echo "$(border)";				\
		i=$$(expr $$i + 1);				\
	done
	@echo -n "\e[$(height)A"
endef

# **************************************************************************** #

.PHONY:	all builtins clean fclean binclean dclean binre re screen
