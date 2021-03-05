# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:27:20 by sadawi            #+#    #+#              #
#    Updated: 2021/03/05 13:03:26 by jwilen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CFILES =  get_env_info.c init_shell.c main.c \
minishell.c 

AUTOCOMPLETE = autocomplete_commands.c autocomplete_commands_alfa.c \
autocomplete_commands_beta.c

BUILTINS = builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c \
builtin_setenv.c builtin_unsetenv.c handle_builtins.c

COMMANDS = commands.c commands_alfa.c commands_beta.c commands_gamma.c \
execute_command.c commands_delta.c commands_epsilon.c

HEREDOC = heredoc.c heredoc_alfa.c heredoc_beta.c heredoc_gamma.c \
heredoc_delta.c

HISTORY = get_history.c history_1.c history_2.c \

INPUT = input_str.c copy.c paste.c expand_input.c \

KEYINPUT = handle_keys.c move_cursor_direction.c move_cursor.c read_key.c \
move_word.c handle_keys_alfa.c

LEXER =  lexi.c lexi2.c token.c token_functions.c \
lexer_alfa.c lexer_collect.c lexer_collect_strings.c

RAWMODE = rawmode.c \

REDIRECTION = redirection.c arg.c \

SHORTCUTS = shortcut_cd.c  shortcut_setenv.c handle_shortcuts.c \

SIGNALS =  handle_signals.c signals.c \

TERMCAPS = termcaps.c \

UTIL = error.c redirect.c cursor.c functions.c strsub_variations.c \
free_memory.c print.c compare_pointers.c


SRCS = $(addprefix srcs/, $(CFILES)) \
$(addprefix srcs/autocomplete/, $(AUTOCOMPLETE)) \
$(addprefix srcs/builtins/, $(BUILTINS)) \
$(addprefix srcs/commands/, $(COMMANDS)) \
$(addprefix srcs/heredoc/, $(HEREDOC)) \
$(addprefix srcs/history/, $(HISTORY)) \
$(addprefix srcs/input/, $(INPUT)) \
$(addprefix srcs/key_input/, $(KEYINPUT)) \
$(addprefix srcs/lexer/, $(LEXER)) \
$(addprefix srcs/rawmode/, $(RAWMODE)) \
$(addprefix srcs/redirection/, $(REDIRECTION)) \
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
