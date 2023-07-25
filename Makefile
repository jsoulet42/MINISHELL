# **************************************************************************** #
#    VARIABLES                                                                 #
# **************************************************************************** #

# *************** #
# Files variables #
# *************** #

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


# ********************* #
# Compilation variables #
# ********************* #

## Compilator and compilation flags
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

## Header files directory
INCL_DIR	=	Includes

## Libraries files directory
LIBS_DIR	=	Libs
## Libraries files names
LIBS		=	-lft -lncurses -lreadline

## Define macros
DEFINES		=	-D_GNU_SOURCE


# ************************* #
# File management variables #
# ************************* #

## Deletion method
RM			=	rm -rf


# ***************** #
# Display variables #
# ***************** #

## Text display delay between characters
ifndef $(SLEEP)
SLEEP		=	0
endif

## Disable fancy mode if not precised at launch
ifndef $(FANCY)
FANCY		=	0
endif

## Color variables
NC			=	"\\e[0m"
BBLACK_FG	=	"\\e[96m"
RED_FG		=	"\\e[91m"
GREEN_FG	=	"\\e[92m"

## Fancy display only
### Minishell startup ascii art
MINI_ASCII		=	":::   :::  :::  :::   :::  :::"\
                 	"\\e[B\\e[31D:+:+ +:+:  +:+  :+:+  :+:  +:+"\
                 	"\\e[B\\e[31D+:+@+:+@+  :+:  +:+@+ +:+  :+:"\
                 	"\\e[B\\e[31D@+@ : @+@  +@+  @+@ :+:+@  +@+"\
                 	"\\e[B\\e[31D+@+   +@+  @+@  +@+  @+@+  @+@"\
                 	"\\e[B\\e[31D@@@   @@@  @@@  @@@   @@@  @@@"

SHELL_ASCII		=	":::::::::  :::   :::  :::::::::  :::        :::"\
                    "\\e[B\\e[48D:+:        +:+   +:+  :+:        +:+        :+:"\
                    "\\e[B\\e[48D+@+        :+:   @+:  +:+        :+@        +:+"\
                    "\\e[B\\e[48D@+@+:+:+@  +@+@+@+:+  @+@+@      +:+        @+@"\
                    "\\e[B\\e[48D      +@+  @+@   @+@  +@+        @+@        +@+"\
                    "\\e[B\\e[48D@@@@@@@@@  @@@   @@@  @@@@@@@@@  @@@@@@@@@  @@@@@@@@@"

### Width and height of the virtual computer's screen
SCREEN_W	=	70

SCREEN_H	=	20

### Virtual computer screen offset from its right frame side
SCREEN_R_OFFSET	=	20

### Characters for display of the virtual computer
SCREEN_BORDER	=	"╔" "═" "╗" "║" "╚" "═" "╝"

### Computer parts colors
FRAME_COLOR		=	$(NC)
KB_COLOR		=	$(NC)
SCREEN_COLOR	=	$(GREEN_FG)
TEXT_COLOR		=	$(GREEN_FG)


# **************************************************************************** #
#    RULES                                                                     #
# **************************************************************************** #

## Main rule
all:	screen builtins $(NAME)


# ********************** #
# Main compilation rules #
# ********************** #

## Main executable compilation
$(NAME):	screen $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS)  $(DEFINES) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	@$(call terminal_disp, "Compiled executable: '$@'", $(TEXT_COLOR))

## Object files compilation rules
$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, "Compiled object file: '$@'", $(TEXT_COLOR))


# ************************** #
# Builtins compilation rules #
# ************************** #

## Builtins executables make rule
builtins:	screen $(ECHO_BIN) $(ENV_BIN) $(PWD_BIN) $(CD_BIN)

## Echo builtin make
$(ECHO_NAME):	$(ECHO_BIN)

## Env builtin make
$(ENV_NAME):	$(ENV_BIN)

## Pwd builtin make
$(PWD_NAME):	$(PWD_BIN)

## Cd builtin make
$(CD_NAME):		$(CD_BIN)

## Echo builtin compilation
$(ECHO_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(ECHO_OBJS)
	@$(CC) $(CFLAGS) $(ECHO_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp,	\
		"Compiled builtin binary: '$(ECHO_NAME)'", $(TEXT_COLOR))

## Env builtin compilation
$(ENV_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(ENV_OBJS)
	@$(CC) $(CFLAGS) $(ENV_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp,	\
		"Compiled builtin binary: '$(ENV_NAME)'", $(TEXT_COLOR))

## Pwd builtin compilation
$(PWD_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(PWD_OBJS)
	@$(CC) $(CFLAGS) $(PWD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp,	\
		"Compiled builtin binary: '$(PWD_NAME)'", $(TEXT_COLOR))

## Cd builtin compilation
$(CD_BIN):	screen $(BIN_DIR) $(OBJS_DIR) $(CD_OBJS)
	@$(CC) $(CFLAGS) $(CD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp,	\
		"Compiled builtin binary: '$(CD_NAME)'", $(TEXT_COLOR))


# **************************** #
# Directories management rules #
# **************************** #

## Object files directory check
$(OBJS_DIR): screen
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 0)
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp,	\
		"Created objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
endif

## Builtins binaries directory check
$(BIN_DIR): screen
ifeq ($(shell if [ -d "$(BIN_DIR)" ]; then echo 1; else echo 0; fi), 0)
	@mkdir $(BIN_DIR)
	@$(call terminal_disp,	\
		"Created binaries directory '$(BIN_DIR)/'", $(TEXT_COLOR))
endif


# ******************** #
# Files deletion rules #
# ******************** #

## Object files deletion
clean: screen
ifneq ($(shell ls $(OBJS_DIR)/*.o 2> /dev/null | wc -l), 0)
	@$(RM) $(OBJS_DIR)/*.o
	@$(call terminal_disp, "Removed object files", $(TEXT_COLOR))
else
	@$(call terminal_disp,	\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)/*.o'", $(TEXT_COLOR))
endif

## Object files and main executable deletion
fclean:	screen clean
ifeq ($(shell if [ -f "$(NAME)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(NAME);
	@$(call terminal_disp, "Removed executable file", $(TEXT_COLOR))
else
	@$(call terminal_disp,	\
		"make: Nothing to be done for '$(RM) $(NAME)'", $(TEXT_COLOR))
endif

## Object files and builtins executables deletion
binclean: screen clean
ifneq ($(shell ls $(BIN_DIR) 2> /dev/null | wc -l), 0)
	@$(RM) $(BIN_DIR)/*
	@$(call terminal_disp, "Removed builtin executable files", $(TEXT_COLOR))
else
	@$(call terminal_disp,	\
		"make: Nothing to be done for '$(RM) $(BIN_DIR)/*'", $(TEXT_COLOR))
endif

## Object files and builtins executables directories deletion
dclean:	screen binclean
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(OBJS_DIR)
	@$(call terminal_disp,	\
		"Removed objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp,	\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)'", $(TEXT_COLOR))
endif
ifeq ($(shell if [ -d "$(BIN_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(BIN_DIR)
	@$(call terminal_disp,	\
		"Removed objects directory '$(BIN_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp,	\
		"make: Nothing to be done for '$(RM) $(BIN_DIR)'", $(TEXT_COLOR))
endif


# ******************* #
# Recompilation rules #
# ******************* #

## Builtins executables recompilation
binre: screen binclean builtins

## Main executable recompilation
minishellre: screen fclean $(NAME)

## Complete recompilation
re:	screen binclean fclean all


# ************* #
# Display rules #
# ************* #

## Virtual computer display
screen:
ifneq ($(FANCY), 0)
	@clear
	@$(call put_screen)
	@$(call put_keyboard)
	@echo -n "\e[s\e[3;4f"
	$(call play_startup)
	@echo -n "\e[s\e[3;4f"
endif


# **************************************************************************** #
#    FUNCTIONS                                                                 #
# **************************************************************************** #

# ***************** #
# Display functions #
# ***************** #

## Shell style character by character test display
define terminal_disp
	$(eval message = $(1))
	$(eval color = $(2))
	@sh_message=$(message);													\
	i=1;																	\
	echo -n "$(color)makefile@minishell $$> ";										\
	while [ $$i -le $${#sh_message} ]; do									\
		echo -n "$$(echo $${sh_message} | cut -c $${i}-$${i})";				\
		if [ $(FANCY) -ne 0 ] && [ $$i -eq $$(( $(SCREEN_W) - 24 )) ]; then	\
			echo -n "\n\e[3C";												\
		fi;																	\
		i=$$(expr $$i + 1);													\
		sleep $(SLEEP);														\
	done
	@echo "$(NC)"
	@if [ $(FANCY) -ne 0 ]; then	\
		echo -n "\e[3C";			\
	fi
endef

## Display of the virtual computer's screen
define put_screen
	$(eval top_l = $(word 1, $(SCREEN_BORDER)))
	$(eval top = $(word 2, $(SCREEN_BORDER)))
	$(eval top_r = $(word 3, $(SCREEN_BORDER)))
	$(eval side = $(word 4, $(SCREEN_BORDER)))
	$(eval bot_l = $(word 5, $(SCREEN_BORDER)))
	$(eval bot = $(word 6, $(SCREEN_BORDER)))
	$(eval bot_r = $(word 7, $(SCREEN_BORDER)))
	$(call put_box_width, $(top_l), $(top), $(top_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET)), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell expr $(SCREEN_H) + 2),	\
		0, $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell expr $(SCREEN_H) + 2),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET) - 1), $(FRAME_COLOR))
	@echo -n "\e[2C"
	$(call put_box_width, $(top_l), $(top), $(top_r), $(SCREEN_W), $(SCREEN_COLOR))
	$(call put_vertical_line, $(side), $(SCREEN_H), 2, $(SCREEN_COLOR))
	$(call put_vertical_line, $(side), $(SCREEN_H),	\
		$(shell expr $(SCREEN_W) + 1), $(SCREEN_COLOR))
	@echo -n "\e[$(SCREEN_H)B\e[2C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r), $(SCREEN_W), $(SCREEN_COLOR))
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET)), $(FRAME_COLOR))
endef

## Display of the virtual computer's keyboard
define put_keyboard
	@echo -n "\e[3C"
	$(call put_box_width, $(top_l), $(top), $(top_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET) - 6), $(KB_COLOR))
	$(call put_vertical_line, $(side), 4, 3, $(KB_COLOR))
	$(call put_vertical_line, $(side), 4,	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET) - 4), $(KB_COLOR))
	@echo -n "\e[4B\e[3C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),	\
		$(shell expr $(SCREEN_W) + $(SCREEN_R_OFFSET) - 6), $(KB_COLOR))
endef

## Display of the top/bottom of an ascii box
define put_box_width
	$(eval left_char = $(1))
	$(eval mid_char = $(2))
	$(eval right_char = $(3))
	$(eval width = $(4))
	$(eval color = $(5))
	@echo -n "$(color)$(left_char)$(NC)";		\
	i=1;										\
	while [ $$i -lt $$(( $(width) - 1 )) ]; do	\
		echo -n "$(color)$(mid_char)$(NC)";		\
		i=$$(expr $$i + 1);						\
	done
	@echo "$(color)$(right_char)$(NC)"
endef

## Display of a vertical line of characters at a specific column
## Returns the cursor at the start of the line's location
define put_vertical_line
	$(eval border = $(1))
	$(eval height = $(2))
	$(eval r_offset = $(3))
	$(eval color = $(4))
	@i=0;								\
	while [ $$i -lt $(height) ]; do		\
		if [ $(r_offset) -gt 0 ]; then	\
			echo -n "\e[$(r_offset)C";	\
		fi;								\
		echo "$(color)$(border)$(NC)";	\
		i=$$(expr $$i + 1);				\
	done
	@echo -n "\e[$(height)A"
endef

define play_startup
	@echo -n "$(TEXT_COLOR)";							\
	if [ $(SCREEN_W) -eq 87 ]; then						\
		echo -n "\e[$$(expr $(SCREEN_H) / 2 - 3)B";		\
		echo -n $(MINI_ASCII);							\
		echo -n "\e[5A\e[2C";							\
		echo -n $(SHELL_ASCII);							\
	elif [ $(SCREEN_W) -gt 87 ]; then					\
		echo -n "\e[$$(expr $(SCREEN_H) / 2 - 3)B";		\
		echo -n "\e[$$(expr $(SCREEN_W) / 2 - 43)C";	\
		echo -n $(MINI_ASCII);							\
		echo -n "\e[5A\e[2C";							\
		echo -n $(SHELL_ASCII);							\
	else												\
		echo -n "\e[$$(expr $(SCREEN_H) / 2 - 6)B";		\
		echo -n "\e[$$(expr $(SCREEN_W) / 2 - 16)C";	\
		echo $(MINI_ASCII);								\
		echo -n "\e[$$(expr $(SCREEN_W) / 2 - 24)C";	\
		echo $(SHELL_ASCII);							\
	fi
	@echo -n "$(NC)"
endef

# **************************************************************************** #

.PHONY:	all builtins clean fclean binclean dclean binre re screen
