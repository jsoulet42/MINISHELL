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
SLEEP		=	0

## Disable fancy mode if not precised at launch
FANCY		=	0

## Color variables
NC			=	"\\e[0m"
INVIS_FG	=	"\\e[90m\\e[100m"
RED_FG		=	"\\e[91m"
GREEN_FG	=	"\\e[92m"
BLACK_BG	=	"\\e[100m"

## Progress bar variables
### Touch
PROG_CHAR	=	"\#"
UNPROG_CHAR	=	" "
### Don't touch
TASKS		=	0
PROGRESS	=	0
CURR_CMD	=	""
PROG_BAR	=	""

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
all:	builtins $(NAME)

# ********************** #
# Main compilation rules #
# ********************** #

## Main executable compilation
$(NAME):	computer init_progress-$(NAME) $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS)  $(DEFINES) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Compiled executable: '$@'", $(TEXT_COLOR))
	@$(eval PROGRESS = $(shell echo $$(( $(PROGRESS) + 1 ))))

## Object files compilation rules
$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Compiled object file: '$@'", $(TEXT_COLOR))
	@$(eval PROGRESS = $(shell echo $$(( $(PROGRESS) + 1 ))))
	@$(call put_loading)


# ************************** #
# Builtins compilation rules #
# ************************** #

## Builtins executables make rule
builtins:	computer init_progress-builtins $(ECHO_BIN) $(ENV_BIN) $(PWD_BIN) $(CD_BIN)
#	@echo "$(TASKS)"

## Echo builtin make
$(ECHO_NAME):	$(ECHO_BIN)

## Env builtin make
$(ENV_NAME):	$(ENV_BIN)

## Pwd builtin make
$(PWD_NAME):	$(PWD_BIN)

## Cd builtin make
$(CD_NAME):		$(CD_BIN)

## Echo builtin compilation
$(ECHO_BIN):	$(BIN_DIR) $(OBJS_DIR) $(ECHO_OBJS)
	@$(CC) $(CFLAGS) $(ECHO_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Compiled builtin binary: '$(ECHO_NAME)'", $(TEXT_COLOR))

## Env builtin compilation
$(ENV_BIN):	$(BIN_DIR) $(OBJS_DIR) $(ENV_OBJS)
	@$(CC) $(CFLAGS) $(ENV_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Compiled builtin binary: '$(ENV_NAME)'", $(TEXT_COLOR))

## Pwd builtin compilation
$(PWD_BIN):	$(BIN_DIR) $(OBJS_DIR) $(PWD_OBJS)
	@$(CC) $(CFLAGS) $(PWD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Compiled builtin binary: '$(PWD_NAME)'", $(TEXT_COLOR))

## Cd builtin compilation
$(CD_BIN):	$(BIN_DIR) $(OBJS_DIR) $(CD_OBJS)
	@$(CC) $(CFLAGS) $(CD_OBJS) -L $(LIBS_DIR) $(LIBS) -o $@
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Compiled builtin binary: '$(CD_NAME)'", $(TEXT_COLOR))


# **************************** #
# Directories management rules #
# **************************** #

## Object files directory check
$(OBJS_DIR):
ifeq ($(shell [ -d "$(OBJS_DIR)" ] && echo 0 || echo 1), 1)
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Created objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
endif

## Builtins binaries directory check
$(BIN_DIR):
ifeq ($(shell [ -d "$(BIN_DIR)" ] && echo 0 || echo 1), 1)
	@mkdir $(BIN_DIR)
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Created binaries directory '$(BIN_DIR)/'", $(TEXT_COLOR))
endif


# ******************** #
# Files deletion rules #
# ******************** #

## Object files deletion
clean:	computer
ifneq ($(shell ls $(OBJS_DIR)/*.o 2> /dev/null | wc -l), 0)
	@$(RM) $(OBJS_DIR)/*.o
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Removed object files", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)/*.o'", $(TEXT_COLOR))
endif

## Object files and main executable deletion
fclean:	computer clean
ifeq ($(shell [ -f "$(NAME)" ] && echo 0 || echo 1), 0)
	@$(RM) $(NAME)
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Removed executable file", $(TEXT_COLOR))
else
	$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"make: Nothing to be done for '$(RM) $(NAME)'", $(TEXT_COLOR))
endif

## Object files and builtins executables deletion
binclean: computer clean
ifneq ($(shell ls $(BIN_DIR) 2> /dev/null | wc -l), 0)
	@$(RM) $(BIN_DIR)/*
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Removed builtin executable files", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"make: Nothing to be done for '$(RM) $(BIN_DIR)/*'", $(TEXT_COLOR))
endif

## Object files and builtins executables directories deletion
dclean:	computer binclean
ifeq ($(shell [ -d "$(OBJS_DIR)" ] && echo 0 || echo 1), 0)
	@$(RM) $(OBJS_DIR)
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Removed objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)'", $(TEXT_COLOR))
endif
ifeq ($(shell [ -d "$(BIN_DIR)" ] && echo 0 || echo 1), 0)
	@$(RM) $(BIN_DIR)
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
		"Removed objects directory '$(BIN_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(SCREEN_W), $(SCREEN_H),\
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


# ********************* #
# Data management rules #
# ********************* #

init_progress-%:
	$(eval PROGRESS = 0)
ifndef CALL_MAKE
	$(eval PROG_BAR = "")
	$(eval CURR_CMD = $(word 2, $(subst -, ,$@)))
	$(eval TASKS = $(shell $(MAKE) -n $(CURR_CMD) CALL_MAKE=0\
		| grep -o '$(CC)\|$(RM)\|mkdir' | wc -l))
endif

## Cap screen width/height and l/r offset values to a minimum
## Get ascii characters for the computer drawing and calculate frame width
check_values:
	$(eval L_OFFSET = $(shell if [ $(L_OFFSET) -lt 0 ];\
		then echo 0; else echo $(L_OFFSET); fi))
	$(eval R_OFFSET = $(shell if [ $(R_OFFSET) -lt 0 ];\
		then echo 0; else echo $(R_OFFSET); fi))
	$(eval SCREEN_W = $(shell if [ $(SCREEN_W) -lt 53 ];\
		then echo 53; else echo $(SCREEN_W); fi))
	$(eval SCREEN_H = $(shell if [ $(SCREEN_H) -lt 12 ];\
		then echo 12; else echo $(SCREEN_H); fi))
	$(eval top_l = $(word 1, $(SCREEN_BORDER)))
	$(eval top = $(word 2, $(SCREEN_BORDER)))
	$(eval top_r = $(word 3, $(SCREEN_BORDER)))
	$(eval side = $(word 4, $(SCREEN_BORDER)))
	$(eval bot_l = $(word 5, $(SCREEN_BORDER)))
	$(eval bot = $(word 6, $(SCREEN_BORDER)))
	$(eval bot_r = $(word 7, $(SCREEN_BORDER)))
	$(eval frame_w =\
		$(shell echo $$(( $(SCREEN_W) + 4 + $(L_OFFSET) + $(R_OFFSET) ))))


# ************* #
# Display rules #
# ************* #

#ifneq ($(words $(MAKECMDGOALS)),1)
#	$(eval cmd = "all")
#else
#	$(eval cmd = "$(MAKECMDGOALS)")
#endif

## Virtual computer display
ifneq ($(FANCY), 0)
computer:	put_screen put_keyboard
	@echo -n "\e[3;$(shell echo $$(( $(L_OFFSET) + 3 )))f"
	$(call play_startup)
	@echo -n "\e[3;$(shell echo $$(( $(L_OFFSET) + 3 )))f\e[s"
endif

## Display the virtual computer's screen
put_screen:	check_values
	@clear
	$(call put_box_width, $(top_l), $(top), $(top_r), $(frame_w), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell echo $$(( $(SCREEN_H) + 2 ))),\
		0, $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell echo $$(( $(SCREEN_H) + 2 ))),\
		$(shell echo $$(( $(frame_w) - 1 ))), $(FRAME_COLOR))
	@echo -n "\e[$(shell echo $$(( $(L_OFFSET) + 1 )))C"
	$(call put_box_width, $(top_l), $(top), $(top_r),\
		$(shell echo $$(( $(SCREEN_W) + 2 ))), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(SCREEN_H),\
		$(shell echo $$(( $(L_OFFSET) + 1 ))), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(SCREEN_H),\
		$(shell echo $$(( $(L_OFFSET) + 2 + $(SCREEN_W) ))), $(FAME_COLOR))
	@echo -n "\e[$(SCREEN_H)B\e[$(shell echo $$(( $(L_OFFSET) + 1 )))C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),\
		$(shell echo $$(( $(SCREEN_W) + 2 ))), $(FRAME_COLOR))
	$(call put_box_width, $(bot_l), $(bot), $(bot_r), $(frame_w), $(FRAME_COLOR))
	@echo -n "\e[s\e[3;$(shell echo $$(( $(L_OFFSET) + 3 )))f"
	$(call put_square, $(SCREEN_COLOR), $(SCREEN_W), $(SCREEN_H))
	@echo -n "\e[u"

## Display the virtual computer's keyboard
put_keyboard:	check_values
	@echo -n "\e[3C"
	$(call put_box_width, $(top_l), $(top), $(top_r),\
		$(shell echo $$(( $(frame_w) - 6 ))), $(KB_COLOR))
	$(call put_vertical_line, $(side), 2, 3, $(KB_COLOR))
	$(call put_vertical_line, $(side), 2,\
		$(shell echo $$(( $(frame_w) - 4 ))), $(KB_COLOR))
	@echo -n "\e[2B\e[3C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),\
		$(shell echo $$(( $(frame_w) - 6 ))), $(KB_COLOR))


# **************************************************************************** #
#    FUNCTIONS                                                                 #
# **************************************************************************** #

# ***************** #
# Display functions #
# ***************** #

#define put_loading
#	$(eval PROG_BAR += $(shell exp $(SCREEN_W)))
#endef

define play_startup
	@echo -n "\e[A\e[s"
	$(call put_makefile_ascii, $(TEXT_COLOR), $(SCREEN_W), $(SCREEN_H))
	@sleep $$(echo "$(SLEEP)" | awk '{print .7 + $$1 * 6}')
	@echo -n "\e[u"
	$(call put_makefile_ascii, $(INVIS_FG), $(SCREEN_W), $(SCREEN_H))
	@echo -n "\e[u\e[B"
	@echo -n "$(TEXT_COLOR)Minicomputer boot..."
	@sleep 0.4
	@echo -n "\e[u\e[B"
	@echo "$(INVIS_FG)                     $(NC)"
endef

## Shell style character by character text display
define terminal_disp
	$(eval width = $(1))
	$(eval height = $(2))
	$(eval message = $(3))
	$(eval color = $(4))
	@sh_message=$(message);													\
	len=$${#sh_message};													\
	echo -n "$(color)makefile@minishell $$> ";								\
	i=1;																	\
	j=23;																	\
	while [ $$i -le $$len ]; do												\
		echo -n "$$(echo $${sh_message} | cut -c $${i}-$${i})";				\
		if [ $(FANCY) -ne 0 ] && [ $$j -eq $(width) ] && [ $$i -ne $$len ];	\
		then																\
			echo -n "\e[B\e[$${j}D";										\
			j=0;															\
		fi;																	\
		i=$$(( $$i + 1 ));													\
		j=$$(( $$j + 1 ));													\
		sleep $(SLEEP);														\
	done;																	\
	echo "$(NC)";															\
	if [ $(FANCY) -ne 0 ]; then												\
		echo -n "\e[$$(( 2 + $(L_OFFSET) ))C";								\
	fi
endef

## Display of the top/bottom of an ascii box
define put_box_width
	$(eval left_char = $(1))
	$(eval mid_char = $(2))
	$(eval right_char = $(3))
	$(eval width = $(4))
	$(eval color = $(5))
	@echo -n "$(color)$(left_char)$(NC)";		\
	line="$(left_chat)";						\
	i=2;										\
	while [ $$i -lt $(width) ]; do				\
		line="$$line$(mid_char)";				\
		i=$$(( $$i + 1 ));						\
	done;										\
	line="$$line$(right_char)";					\
	echo "$(color)$$line$(NC)"
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
			echo -n "\e[$(r_offset)C";		\
		fi;									\
		echo "$(color)$(border)$(NC)";		\
		i=$$(( $$i + 1 ));					\
	done;									\
	echo -n "\e[$(height)A"
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
	echo -n "$(color)$$square$(NC)"
endef

## Print the minishell ascii art centered inside a width and height area
define put_makefile_ascii
	$(eval color = $(1))
	$(eval width = $(2))
	$(eval height = $(3))
	@echo -n "$(color)";							\
	if [ $(width) -eq 85 ]; then					\
		echo -n "\e[$$(expr $(height) / 2 - 3)B";	\
		echo -n $(MINI_ASCII);						\
		echo -n "\e[5A\e[2C";						\
		echo -n $(SHELL_ASCII);						\
	elif [ $(width) -gt 85 ]; then					\
		echo -n "\e[$$(expr $(height) / 2 - 3)B";	\
		echo -n "\e[$$(expr $(width) / 2 - 43)C";	\
		echo -n $(MINI_ASCII);						\
		echo -n "\e[5A\e[2C";						\
		echo -n $(SHELL_ASCII);						\
	else											\
		echo -n "\e[$$(expr $(height) / 2 - 6)B";	\
		echo -n "\e[$$(expr $(width) / 2 - 16)C";	\
		echo -n $(MINI_ASCII)"\e[B";				\
		echo -n "\e[40D";							\
		echo -n $(SHELL_ASCII);						\
	fi
	@echo -n "$(NC)"
endef

# **************************************************************************** #

.PHONY:	all builtins $(ECHO_NAME) $(ENV_NAME) $(PWD_NAME) $(CD_NAME) clean\
		fclean binclean dclean binre re computer check_values put_screen\
		put_keyboard
