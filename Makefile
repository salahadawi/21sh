# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:27:20 by sadawi            #+#    #+#              #
#    Updated: 2021/02/15 14:36:23 by jwilen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CFILES = compare_pointers.c execute_command.c expand_input.c free_memory.c \
get_env_info.c init_shell.c main.c \
minishell.c print.c split_input.c strsub_variations.c

AST = parse.c recursive_build.c syntax_check.c \

AUTOCOMPLETE = autocomplete_commands.c autocomplete_commands_alfa.c \
autocomplete_commands_beta.c

BUILTINS = builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c \
builtin_setenv.c builtin_unsetenv.c handle_builtins.c

COMMANDS = commands.c commands_alfa.c commands_beta.c commands_gamma.c \

HEREDOC = heredoc.c heredoc_alfa.c heredoc_beta.c heredoc_gamma.c \
heredoc_delta.c

HISTORY = get_history.c history_1.c history_2.c \

INPUT = input_str.c copy.c paste.c \

KEYINPUT = handle_keys.c move_cursor_direction.c move_cursor.c read_key.c \
move_word.c

LEXER =  lexi.c lexi2.c token.c convert_tokens.c \

RAWMODE = rawmode.c \

SHORTCUTS = shortcut_cd.c  shortcut_setenv.c handle_shortcuts.c \

SIGNALS =  handle_signals.c signals.c \

TERMCAPS = termcaps.c \

UTIL = error.c \


SRCS = $(addprefix srcs/, $(CFILES)) \
$(addprefix srcs/ast/, $(AST)) \
$(addprefix srcs/autocomplete/, $(AUTOCOMPLETE)) \
$(addprefix srcs/builtins/, $(BUILTINS)) \
$(addprefix srcs/commands/, $(COMMANDS)) \
$(addprefix srcs/heredoc/, $(HEREDOC)) \
$(addprefix srcs/history/, $(HISTORY)) \
$(addprefix srcs/input/, $(INPUT)) \
$(addprefix srcs/key_input/, $(KEYINPUT)) \
$(addprefix srcs/lexer/, $(LEXER)) \
$(addprefix srcs/rawmode/, $(RAWMODE)) \
$(addprefix srcs/shortcuts/, $(SHORTCUTS)) \
$(addprefix srcs/signals/, $(SIGNALS)) \
$(addprefix srcs/termcaps/, $(TERMCAPS)) \
$(addprefix srcs/util/, $(UTIL)) \

OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))

INCLUDES = -I includes -I libft/includes

FLAGS = -Wall -Wextra -Werror -g

RUN_LIB = make --no-print-directory -C libft/

all:
	@$(RUN_LIB)
	@make --no-print-director $(NAME)

$(NAME): $(SRCS) libft/
	@rm -rf objs
	@echo Compiling $(NAME)...
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) libft/libft.a -ltermcap
	@echo $(NAME) compiled succesfully!

lib:
	@$(RUN_LIB)

noflags: $(SRCS) libft/
	@rm -rf objs
	@echo Compiling $(NAME) without flags...
	@gcc $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc $(INCLUDES) -o $(NAME) $(OBJS) libft/libft.a -ltermcap
	@echo $(NAME) compiled without flags succesfully!

debug: $(SRCS) libft/
	@rm -rf objs
	@echo Compiling $(NAME) with debug flag...
	@gcc -g $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc -g $(INCLUDES) -o $(NAME) $(OBJS) libft/libft.a -ltermcap
	@echo $(NAME) compiled with debug flag succesfully!

clean:
	@/bin/rm -f $(OBJS)
	@rm -rf objs
	@make -C libft/ clean
	@echo Clean successful!

clean_binary:
	@/bin/rm -f $(OBJS)
	@rm -rf objs
	@echo Clean successful!

fclean: clean_binary
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@echo Clean successful!

re: fclean all
