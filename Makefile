# **************************************************************************** #
#    VARIABLES                                                                 #
# **************************************************************************** #

# *************** #
# Files variables #
# *************** #

SHELL		=	/bin/bash

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
SLEEP		=	0

## Disable fancy mode if not precised at launch
FANCY		=	0

## Color variables
NC			=	"\\e[0m"
INVIS_FG	=	"\\e[90m\\e[100m"
RED_FG		=	"\\e[91m"
GREEN_FG	=	"\\e[92m"
BLACK_BG	=	"\\e[100m"

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

### Virtual computer screen offset from its left and right frame sides
L_OFFSET	=	5
R_OFFSET	=	20

### Characters for display of the virtual computer
SCREEN_BORDER	=	"╔" "═" "╗" "║" "╚" "═" "╝"

### Computer parts colors
FRAME_COLOR		=	$(NC)
KB_COLOR		=	$(NC)
SCREEN_COLOR	=	$(BLACK_BG)
ifneq ($(FANCY), 0)
TEXT_COLOR		=	$(GREEN_FG)$(BLACK_BG)
endif


# **************************************************************************** #
#    RULES                                                                     #
# **************************************************************************** #

## Main rule
all:	computer builtins $(NAME)


# ********************** #
# Main compilation rules #
# ********************** #

## Main executable compilation
$(NAME):	computer $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS)  $(DEFINES) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Compiled executable: '$@'", $(TEXT_COLOR))

## Object files compilation rules
$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Compiled object file: '$@'", $(TEXT_COLOR))


# ************************** #
# Builtins compilation rules #
# ************************** #

## Builtins executables make rule
builtins:	computer $(ECHO_BIN) $(ENV_BIN) $(PWD_BIN) $(CD_BIN)

## Echo builtin make
$(ECHO_NAME):	$(ECHO_BIN)

## Env builtin make
$(ENV_NAME):	$(ENV_BIN)

## Pwd builtin make
$(PWD_NAME):	$(PWD_BIN)

## Cd builtin make
$(CD_NAME):		$(CD_BIN)

## Echo builtin compilation
$(ECHO_BIN):	computer $(BIN_DIR) $(OBJS_DIR) $(ECHO_OBJS)
	@$(CC) $(CFLAGS) $(ECHO_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Compiled builtin binary: '$(ECHO_NAME)'", $(TEXT_COLOR))

## Env builtin compilation
$(ENV_BIN):	computer $(BIN_DIR) $(OBJS_DIR) $(ENV_OBJS)
	@$(CC) $(CFLAGS) $(ENV_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Compiled builtin binary: '$(ENV_NAME)'", $(TEXT_COLOR))

## Pwd builtin compilation
$(PWD_BIN):	computer $(BIN_DIR) $(OBJS_DIR) $(PWD_OBJS)
	@$(CC) $(CFLAGS) $(PWD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Compiled builtin binary: '$(PWD_NAME)'", $(TEXT_COLOR))

## Cd builtin compilation
$(CD_BIN):	computer $(BIN_DIR) $(OBJS_DIR) $(CD_OBJS)
	@$(CC) $(CFLAGS) $(CD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Compiled builtin binary: '$(CD_NAME)'", $(TEXT_COLOR))


# **************************** #
# Directories management rules #
# **************************** #

## Object files directory check
$(OBJS_DIR): computer
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 0)
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Created objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
endif

## Builtins binaries directory check
$(BIN_DIR): computer
ifeq ($(shell if [ -d "$(BIN_DIR)" ]; then echo 1; else echo 0; fi), 0)
	@mkdir $(BIN_DIR)
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Created binaries directory '$(BIN_DIR)/'", $(TEXT_COLOR))
endif


# ******************** #
# Files deletion rules #
# ******************** #

## Object files deletion
clean: computer
ifneq ($(shell ls $(OBJS_DIR)/*.o 2> /dev/null | wc -l), 0)
	@$(RM) $(OBJS_DIR)/*.o
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Removed object files", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)/*.o'", $(TEXT_COLOR))
endif

## Object files and main executable deletion
fclean:	computer clean
ifeq ($(shell if [ -f "$(NAME)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(NAME);
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Removed executable file", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"make: Nothing to be done for '$(RM) $(NAME)'", $(TEXT_COLOR))
endif

## Object files and builtins executables deletion
binclean: computer clean
ifneq ($(shell ls $(BIN_DIR) 2> /dev/null | wc -l), 0)
	@$(RM) $(BIN_DIR)/*
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Removed builtin executable files", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"make: Nothing to be done for '$(RM) $(BIN_DIR)/*'", $(TEXT_COLOR))
endif

## Object files and builtins executables directories deletion
dclean:	computer binclean
ifeq ($(shell if [ -d "$(OBJS_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(OBJS_DIR)
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Removed objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)'", $(TEXT_COLOR))
endif
ifeq ($(shell if [ -d "$(BIN_DIR)" ]; then echo 1; else echo 0; fi), 1)
	@$(RM) $(BIN_DIR)
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"Removed objects directory '$(BIN_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(used_screenw), $(used_screenh),\
		"make: Nothing to be done for '$(RM) $(BIN_DIR)'", $(TEXT_COLOR))
endif


# ******************* #
# Recompilation rules #
# ******************* #

## Builtins executables recompilation
binre: computer binclean builtins

## Main executable recompilation
minishellre: computer fclean $(NAME)

## Complete recompilation
re:	computer binclean fclean all


# ************* #
# Display rules #
# ************* #

## Virtual computer display
ifneq ($(FANCY), 0)
computer:	check_values put_screen put_keyboard
	@echo -en "\e[3;$(shell expr $(used_loffset) + 3)f"
	$(call play_startup)
	@echo -en "\e[3;$(shell expr $(used_loffset) + 3)f\e[s"
endif

## Cap screen width/height and l/r offset values to a minimum
## Get ascii characters for the computer drawing and calculate frame width
check_values:
	$(eval used_loffset = $(shell if [ $(L_OFFSET) -lt 0 ];\
		then echo 0; else echo $(L_OFFSET); fi))
	$(eval used_roffset = $(shell if [ $(R_OFFSET) -lt 0 ];\
		then echo 0; else echo $(R_OFFSET); fi))
	$(eval used_screenw = $(shell if [ $(SCREEN_W) -lt 53 ];\
		then echo 53; else echo $(SCREEN_W); fi))
	$(eval used_screenh = $(shell if [ $(SCREEN_H) -lt 12 ];\
		then echo 12; else echo $(SCREEN_H); fi))
	$(eval top_l = $(word 1, $(SCREEN_BORDER)))
	$(eval top = $(word 2, $(SCREEN_BORDER)))
	$(eval top_r = $(word 3, $(SCREEN_BORDER)))
	$(eval side = $(word 4, $(SCREEN_BORDER)))
	$(eval bot_l = $(word 5, $(SCREEN_BORDER)))
	$(eval bot = $(word 6, $(SCREEN_BORDER)))
	$(eval bot_r = $(word 7, $(SCREEN_BORDER)))
	$(eval frame_w =\
		$(shell expr $(used_screenw) + 4 + $(used_loffset) + $(used_roffset)))

## Display the virtual computer's screen
put_screen:
	@clear
	$(call put_box_width, $(top_l), $(top), $(top_r), $(frame_w), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell expr $(SCREEN_H) + 2),\
		0, $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell expr $(SCREEN_H) + 2),\
		$(shell expr $(frame_w) - 1), $(FRAME_COLOR))
	@echo -en "\e[$(shell expr $(used_loffset) + 1)C"
	$(call put_box_width, $(top_l), $(top), $(top_r),\
		$(shell expr $(used_screenw) + 2), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(SCREEN_H),\
		$(shell expr $(used_loffset) + 1), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(SCREEN_H),\
		$(shell expr $(used_loffset) + 2 + $(used_screenw)), $(FAME_COLOR))
	@echo -en "\e[$(SCREEN_H)B\e[$(shell expr $(used_loffset) + 1)C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),\
		$(shell expr $(used_screenw) + 2), $(FRAME_COLOR))
	$(call put_box_width, $(bot_l), $(bot), $(bot_r), $(frame_w), $(FRAME_COLOR))
	@echo -en "\e[s\e[3;$(shell expr $(used_loffset) + 3)f"
	$(call put_square, $(SCREEN_COLOR), $(used_screenw), $(SCREEN_H))
	@echo -en "\e[u"

## Display the virtual computer's keyboard
put_keyboard:
	@echo -en "\e[3C"
	$(call put_box_width, $(top_l), $(top), $(top_r),\
		$(shell expr $(frame_w) - 6), $(KB_COLOR))
	$(call put_vertical_line, $(side), 2, 3, $(KB_COLOR))
	$(call put_vertical_line, $(side), 2,\
		$(shell expr $(frame_w) - 4), $(KB_COLOR))
	@echo -en "\e[2B\e[3C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),\
		$(shell expr $(frame_w) - 6 ), $(KB_COLOR))


# **************************************************************************** #
#    FUNCTIONS                                                                 #
# **************************************************************************** #

# ***************** #
# Display functions #
# ***************** #

define play_startup
	@echo -en "\e[A\e[s"
	$(call put_makefile_ascii, $(TEXT_COLOR), $(used_screenw), $(used_screenh))
	@sleep $$(( 1 + $(SLEEP) ))
	@echo -en "\e[u"
	$(call put_makefile_ascii, $(INVIS_FG), $(used_screenw), $(used_screenh))
	@echo -en "\e[u\e[B"
	@echo -e "$(TEXT_COLOR)Minicomputer boot..."
	@sleep 0.4
	@echo -en "\e[u\e[B"
	@echo -e "$(INVIS_FG)                     $(NC)"
endef

## Shell style character by character text display
define terminal_disp
	$(eval width = $(1))
	$(eval height = $(2))
	$(eval message = $(3))
	$(eval color = $(4))
	@sh_message=$(message);													\
	len=$${#sh_message};													\
	echo -en "$(color)makefile@minishell $$> ";								\
	i=1;																	\
	j=23;																	\
	while [ $$i -le $$len ]; do												\
		echo -en "$$(echo $${sh_message} | cut -c $${i}-$${i})";			\
		if [ $(FANCY) -ne 0 ] && [ $$j -eq $(width) ] && [ $$i -ne $$len ];	\
		then																\
			echo -en "\e[B\e[$${j}D";										\
			j=0;															\
		fi;																	\
		i=$$(( $$i + 1 ));													\
		j=$$(( $$j + 1 ));													\
		sleep $(SLEEP);														\
	done;																	\
	echo -e "$(NC)";														\
	if [ $(FANCY) -ne 0 ]; then												\
		echo -en "\e[$$(( 2 + $(used_loffset) ))C";							\
	fi
endef

## Display of the top/bottom of an ascii box
define put_box_width
	$(eval left_char = $(1))
	$(eval mid_char = $(2))
	$(eval right_char = $(3))
	$(eval width = $(4))
	$(eval color = $(5))
	@echo -en "$(color)$(left_char)$(NC)";		\
	line="$(left_chat)";						\
	i=2;										\
	while [ $$i -lt $(width) ]; do				\
		line="$$line$(mid_char)";				\
		i=$$(( $$i + 1 ));						\
	done;										\
	line="$$line$(right_char)";					\
	echo -e "$(color)$$line$(NC)"
endef

## Display of a vertical line of characters at a specific column
## Returns the cursor at the start of the line's location
define put_vertical_line
	$(eval border = $(1))
	$(eval height = $(2))
	$(eval r_offset = $(3))
	$(eval color = $(4))
	@i=0;									\
	while [ $$i -lt $(height) ]; do			\
		if [ $(r_offset) -gt 0 ]; then		\
			echo -en "\e[$(r_offset)C";		\
		fi;									\
		echo -e "$(color)$(border)$(NC)";	\
		i=$$(( $$i + 1 ));					\
	done;									\
	echo -en "\e[$(height)A"
endef

## Print a square of a given color
define put_square
	$(eval color = $(1))
	$(eval width = $(2))
	$(eval height = $(3))
	@line=" ";										\
	x=1;											\
	while [ $$x -lt $(width) ]; do					\
		line="$$line ";								\
		x=$$(( $$x + 1 ));							\
	done;											\
	square="$$line\e[B\e[$(width)D";				\
	y=1;											\
	while [ $$y -lt $(height) ]; do					\
		square="$$square$$line\e[B\e[$(width)D";	\
		y=$$(( $$y + 1 ));							\
	done;											\
	echo -en "$(color)$$square$(NC)"
endef

## Print the minishell ascii art centered inside a width and height area
define put_makefile_ascii
	$(eval color = $(1))
	$(eval width = $(2))
	$(eval height = $(3))
	@echo -en "$(color)";							\
	if [ $(width) -eq 85 ]; then					\
		echo -en "\e[$$(expr $(height) / 2 - 3)B";	\
		echo -en $(MINI_ASCII);						\
		echo -en "\e[5A\e[2C";						\
		echo -en $(SHELL_ASCII);						\
	elif [ $(width) -gt 85 ]; then					\
		echo -en "\e[$$(expr $(height) / 2 - 3)B";	\
		echo -en "\e[$$(expr $(width) / 2 - 43)C";	\
		echo -en $(MINI_ASCII);						\
		echo -en "\e[5A\e[2C";						\
		echo -en $(SHELL_ASCII);						\
	else											\
		echo -en "\e[$$(expr $(height) / 2 - 6)B";	\
		echo -en "\e[$$(expr $(width) / 2 - 16)C";	\
		echo -en $(MINI_ASCII)"\e[B";				\
		echo -en "\e[40D";							\
		echo -e $(SHELL_ASCII);						\
	fi
	@echo -e "$(NC)"
endef

# **************************************************************************** #

.PHONY:	all builtins clean fclean binclean dclean binre re computer\
		check_values put_screen put_keyboard
