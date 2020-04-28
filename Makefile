# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:27:20 by sadawi            #+#    #+#              #
#    Updated: 2020/04/28 19:33:50 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFILES = compare_pointers.c execute_command.c expand_input.c free_memory.c \
get_env_info.c handle_builtins.c handle_shortcuts.c init_shell.c main.c \
minishell.c print.c split_input.c strsub_variations.c

BUILTINS = builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c \
builtin_setenv.c builtin_unsetenv.c

SHORTCUTS = shortcut_cd.c  shortcut_setenv.c

SRCS = $(addprefix srcs/, $(CFILES)) $(addprefix srcs/builtins/, $(BUILTINS)) \
$(addprefix srcs/shortcuts/, $(SHORTCUTS))

OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))

INCLUDES = -I includes -I libft/includes

FLAGS = -Wall -Wextra -Werror

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

noflags:
	@rm -rf objs
	@echo Compiling $(NAME) without flags...
	@gcc $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc $(INCLUDES) -o $(NAME) $(OBJS) libft/libft.a -ltermcap
	@echo $(NAME) compiled without flags succesfully!

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
