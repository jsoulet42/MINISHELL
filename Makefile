# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 12:13:07 by hnogared          #+#    #+#              #
#    Updated: 2023/08/24 17:27:25 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES                                                                 #
# **************************************************************************** #

# *************** #
# Files variables #
# *************** #

## Executable name
NAME		=	minishell

## Paths to all source files
VPATH		=	Srcs:			\
				Srcs/builtins:

SRCS		=	main.c						\
				parsing_01.c				\
				parsing_02.c				\
				parsing_03.c				\
				parsing_04.c				\
				parsing_05.c				\
				parsing_06.c				\
				parsing_07.c				\
				parsing_08.c				\
				doublquote_01.c				\
				simplquote_01.c				\
				display.c					\
				init_environment.c			\
				environment_utils_01.c		\
				environment_utils_02.c		\
				environment_utils_03.c		\
				free_utils_01.c				\
				utils.c						\
				check_starterrors01.c		\
				check_starterrors02.c		\
				ft_heredoc.c				\
				interpret_01.c				\
				interpret_02.c				\
				interpret_03.c				\
				interpret_04.c				\
				ft_export.c					\
				get_next_line_bonus.c		\
				get_next_line_utils_bonus.c \
				lentab.c					\
				ft_cd.c						\
				ft_unset.c					\
				ft_exit.c					\
				ft_echo.c					\
				ft_pwd.c					\
				ft_env.c					\
				modif_shlvl.c				\
				signals.c

## Object files directory
OBJS_DIR	=	Objs

## Object files names
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))


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

## Makefile prompt
PROMPT		=	"makefile@minishell $$> "

## Animations slowdown
SLEEP		=	0

## Default fancy display (0 = OFF / > 0 = ON)
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

## Progress bar characters
PROG_CHAR	=	"@"
UNPROG_CHAR	=	" "


# **************************************************************************** #
#    RULES                                                                     #
# **************************************************************************** #

## Main rule
all:	init builtins $(NAME)

# ********************** #
# Main compilation rules #
# ********************** #

## Main executable compilation
$(NAME):	init init_progress-$(NAME) $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS)  $(DEFINES) $(OBJS) -L $(LIBS_DIR) $(LIBS) -o $@ $(LDLIBS)
	$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"Compiled executable: '$@'", $(TEXT_COLOR))
#	$(eval progress = $(shell echo $$(( $(progress) + 1 ))))
#	$(call put_loading, $(progress), $(tasks), $(_screen_w), $(_screen_h))

## Object files compilation rules
$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -L $(LIBS_DIR) $(LIBS) -o $@
	$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"Compiled object file: '$@'", $(TEXT_COLOR))
#	$(eval progress = $(shell echo $$(( $(progress) + 1 ))))
#	$(call put_loading, $(progress), $(tasks), $(_screen_w), $(_screen_h))

## Complete recompilation
re:	init fclean all


# **************************** #
# Directories management rules #
# **************************** #

## Object files directory check
$(OBJS_DIR):
ifeq ($(shell [ -d "$(OBJS_DIR)" ] && echo 0 || echo 1), 1)
	@mkdir $(OBJS_DIR)
	@$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"Created objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
endif


# ******************** #
# Files deletion rules #
# ******************** #

## Object files deletion
clean:	init
ifneq ($(shell ls $(OBJS_DIR)/*.o 2> /dev/null | wc -l), 0)
	@$(RM) $(OBJS_DIR)/*.o
	@$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"Removed object files", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)/*.o'", $(TEXT_COLOR))
endif

## Object files and main executable deletion
fclean:	init clean
ifeq ($(shell [ -f "$(NAME)" ] && echo 0 || echo 1), 0)
	@$(RM) $(NAME)
	@$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"Removed executable file", $(TEXT_COLOR))
else
	$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"make: Nothing to be done for '$(RM) $(NAME)'", $(TEXT_COLOR))
endif

## Object files and builtins executables directories deletion
dclean:	init
ifeq ($(shell [ -d "$(OBJS_DIR)" ] && echo 0 || echo 1), 0)
	@$(RM) $(OBJS_DIR)
	@$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"Removed objects directory '$(OBJS_DIR)/'", $(TEXT_COLOR))
else
	@$(call terminal_disp, $(_screen_w), $(_screen_h),\
		"make: Nothing to be done for '$(RM) $(OBJS_DIR)'", $(TEXT_COLOR))
endif


# ********************* #
# Data management rules #
# ********************* #

init:	init_values computer

init_progress-%:
	$(eval progress = 0)
ifndef CALL_MAKE
	$(eval curr_cmd = $(word 2, $(subst -, ,$@)))
	$(eval tasks = $(shell $(MAKE) -n $(curr_cmd) CALL_MAKE=0\
		| grep -o '$(CC)\|$(RM)\|mkdir' | wc -l))
endif

## Cap screen width/height and l/r offset values to a minimum
## Get ascii characters for the computer drawing
## Calculate frame width
## Init progress bar variables
init_values:
	$(eval _l_offset != [ $(L_OFFSET) -lt 0 ] && echo 0 ||echo $(L_OFFSET))
	$(eval _r_offset != [ $(R_OFFSET) -lt 0 ] && echo 0 || echo $(R_OFFSET))
	$(eval _screen_w != [ $(SCREEN_W) -lt 53 ] && echo 53 || echo $(SCREEN_W))
	$(eval _screen_h != [ $(SCREEN_H) -lt 12 ] && echo 12 || echo $(SCREEN_H))
	$(eval top_l = $(word 1, $(SCREEN_BORDER)))
	$(eval top = $(word 2, $(SCREEN_BORDER)))
	$(eval top_r = $(word 3, $(SCREEN_BORDER)))
	$(eval side = $(word 4, $(SCREEN_BORDER)))
	$(eval bot_l = $(word 5, $(SCREEN_BORDER)))
	$(eval bot = $(word 6, $(SCREEN_BORDER)))
	$(eval bot_r = $(word 7, $(SCREEN_BORDER)))
	$(eval frame_w =\
		$(shell echo $$(( $(_screen_w) + 4 + $(_l_offset) + $(_r_offset) ))))
	$(eval max_prog_bar != printf "%$(_screen_w)s" | tr " " $(PROG_CHAR))
	$(eval max_unprog_bar != printf "%$(_screen_w)s" | tr " " $(UNPROG_CHAR))
	$(eval tasks = 0)
	$(eval line_cnt = 0)


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
	@echo -n "\e[3;$(shell echo $$(( $(_l_offset) + 3 )))f"
	$(call play_startup)
	@echo -n "\e[3;$(shell echo $$(( $(_l_offset) + 3 )))f\e[s"
endif

## Display the virtual computer's screen
put_screen:	init_values
	@clear
	$(call put_box_width, $(top_l), $(top), $(top_r), $(frame_w), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell echo $$(( $(_screen_h) + 2 ))),\
		0, $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(shell echo $$(( $(_screen_h) + 2 ))),\
		$(shell echo $$(( $(frame_w) - 1 ))), $(FRAME_COLOR))
	@echo -n "\e[$(shell echo $$(( $(_l_offset) + 1 )))C"
	$(call put_box_width, $(top_l), $(top), $(top_r),\
		$(shell echo $$(( $(_screen_w) + 2 ))), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(_screen_h),\
		$(shell echo $$(( $(_l_offset) + 1 ))), $(FRAME_COLOR))
	$(call put_vertical_line, $(side), $(_screen_h),\
		$(shell echo $$(( $(_l_offset) + 2 + $(_screen_w) ))), $(FAME_COLOR))
	@echo -n "\e[$(_screen_h)B\e[$(shell echo $$(( $(_l_offset) + 1 )))C"
	$(call put_box_width, $(bot_l), $(bot), $(bot_r),\
		$(shell echo $$(( $(_screen_w) + 2 ))), $(FRAME_COLOR))
	$(call put_box_width, $(bot_l), $(bot), $(bot_r), $(frame_w), $(FRAME_COLOR))
	@echo -n "\e[s\e[3;$(shell echo $$(( $(_l_offset) + 3 )))f"
	$(call put_square, $(SCREEN_COLOR), $(_screen_w), $(_screen_h))
	@echo -n "\e[u"

## Display the virtual computer's keyboard
put_keyboard:	init_values
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

define put_loading
	$(eval progress = $(1))
	$(eval tasks = $(2))
	$(eval width = $(3))
	$(eval height = $(4))
	@echo -n "\e[$(height)B";														\
	printf "%.*s\n" $$(( $(progress) * $(width) / $(tasks) )) "$(max_prog_bar)";	\
	echo -n "\e[$(height)A"
endef

define play_startup
	@echo -n "\e[A\e[s"
	$(call put_makefile_ascii, $(TEXT_COLOR), $(_screen_w), $(_screen_h))
	@sleep $$(echo "$(SLEEP)" | awk '{print .7 + $$1 * 6}')
	@echo -n "\e[u"
	$(call put_makefile_ascii, $(INVIS_FG), $(_screen_w), $(_screen_h))
	@echo -n "\e[u\e[B"
	@echo -n "$(TEXT_COLOR)Minicomputer boot..."
	@sleep 0.4
	@echo -n "\e[u\e[B"
	@echo "$(INVIS_FG)                     $(NC)"
endef

define new_line
	$(eval width = $(1))
	$(eval height = $(2))
	$(eval message = $(3))
	$(eval message_len = $(shell echo $(PROMPT)$(message) | wc -c))
	$(eval line_cnt = $(shell echo $$(( $(line_cnt)\
		+ ($(message_len) / $(width) + 1) ))))
	@echo -n "\e[$$(( 2 + $(_l_offset) ))C";	\
	if [ $(line_cnt) -ge $(height) ]; then	\
		echo -n "\e[3;$$(( $(_l_offset) + 3 ))f\e[s";\
		true $(call put_square, $(SCREEN_COLOR), $(width), $(height));	\
		echo -n "\e[u";\
		true $(eval line_cnt = 0);\
	fi

endef

## Stylized character by character text display
define terminal_disp
	$(eval width = $(1))
	$(eval height = $(2))
	$(eval message = $(3))
	$(eval color = $(4))
	@sh_message=$(message);													\
	len=$${#sh_message};													\
	echo -n $(color)$(PROMPT);												\
	i=1;																	\
	j=$$(echo $(PROMPT) | wc -c);											\
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
	echo "$(NC)"
	$(if $(shell [ $(FANCY) -ne 0 ] && echo "true"),\
		$(call new_line, $(width), $(height), $(message)))
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
