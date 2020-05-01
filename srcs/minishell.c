/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2020/05/01 19:23:40 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		read_key(void)
{
	char sequence[10];

	if (read(STDOUT_FILENO, sequence, 10) == -1)
		handle_error("Read failed", 1);
	if (sequence[0] == ESCAPE)
	{
		if (sequence[1] == '[')
			return (sequence[2] - 100);
	}
	return (sequence[0]);
}

char	*str_remove_char(char *str, int index)
{
	int		i;
	char	*newstr;

	if (index < 0 || index >= (int)ft_strlen(str))
		return (str);
	newstr = (char*)malloc(ft_strlen(str));
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	if (!str[i])
	{
		free(str);
		return (newstr);
	}
	while (str[i + 1])
	{
		newstr[i] = str[i + 1];
		i++;
	}
	newstr[i] = '\0';
	free(str);
	return (newstr);
}

char	*str_add_char(char *str, char c)
{
	int		i;
	int		index;
	char	*newstr;

	index = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	newstr = (char*)malloc(ft_strlen(str) + 2);
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	while (str[i])
	{
		newstr[i + 1] = str[i];
		i++;
	}
	newstr[i + 1] = '\0';
	free(str);
	return (newstr);
}

void	move_cursor_left(void)
{
	if ((int)ft_strlen(g_21sh->line) > -g_21sh->cursor.x)
		g_21sh->cursor.x--;
}

void	move_cursor_right(void)
{
	if (g_21sh->cursor.x < 0)
		g_21sh->cursor.x++;
}

void	handle_delete(void)
{
	g_21sh->line = str_remove_char(g_21sh->line, ft_strlen(g_21sh->line)
	+ g_21sh->cursor.x);
	move_cursor_right();
}

void	handle_control_sequence(char *c)
{
	*c += 100;
	
	if (*c == g_21sh->key_sequences.delete)
		handle_delete();
	else if (*c == g_21sh->key_sequences.left_arrow)
		move_cursor_left();
	else if (*c == g_21sh->key_sequences.right_arrow)
		move_cursor_right();
	else if (*c == g_21sh->key_sequences.up_arrow)
		;
	else if (*c == g_21sh->key_sequences.down_arrow)
	{
			;
	}
	else if (*c == HOME)
		g_21sh->cursor.x = -ft_strlen(g_21sh->line);
	else if (*c == END)
		g_21sh->cursor.x = 0;	
}

void	handle_backspace(void)
{
	g_21sh->line = str_remove_char(g_21sh->line, ft_strlen(g_21sh->line)
	+ g_21sh->cursor.x - 1);
}

int		handle_keys(void)
{
	char c;

	c = read_key();
	//ft_printf("%d", c);
	if (c == 0)
		return (1);
	if (c < 0)
	{
		handle_control_sequence(&c);
		return (1);
	}
	if (c == BACKSPACE)
	{
		handle_backspace();
	}
	else if (c == ENTER)
		return (0);
	else if (c == 4)
		exit(0); //temporary, need to restore terminal and free memory here
	else
		g_21sh->line = str_add_char(g_21sh->line, c);
	return (1);
}

void	move_cursor_start(void)
{
	char *move_cursor;
	char *tmp;

	move_cursor = tgetstr("cm", NULL);
	//ft_printf("%d, %d", g_21sh->cursor.prompt_y, g_21sh->cursor.prompt_x);
	tmp = tgoto(move_cursor, g_21sh->cursor.prompt_x - 1, g_21sh->cursor.prompt_y - 1);
	tputs(tmp, 1, ft_putschar);
}

void	move_cursor(void)
{
	int len;

	len = g_21sh->cursor.x;
	while (len++ < 0)
		set_terminal("le");
}

int		ft_nbrlen(int nbr)
{
	int i;

	i = 0;
	while (nbr || !i)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position()
{
	char	sequence[10];
	int		i;
	int		x;
	int		y;

	ft_printf("%s", "\x1b[6n");
	read(0, sequence, 10);
	i = 0;
	while (sequence[i] != '[' && i < 10)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 + ft_nbrlen(y)]);
	g_21sh->cursor.prompt_y = y ? y : g_21sh->cursor.prompt_y;
	g_21sh->cursor.prompt_x = x ? x : g_21sh->cursor.prompt_x;// + g_21sh->prompt_len;
	//ft_printf("%s", &sequence[i]);
}

int		get_input()
{
	g_21sh->line = ft_strnew(0);
	get_cursor_position();
	while (handle_keys())
	{
		move_cursor_start();
		set_terminal("cd");
		ft_printf("%s", g_21sh->line);
		move_cursor();
	}
	return (1);
}

void	loop_shell(void)
{
	char	**commands;
	char	**args;
	int		loop;
	int		i;

	loop = 1;
	while (loop)
	{
		g_21sh->cursor.x = 0;
		print_shell_info();
		if (get_input() < 1)
			break ;
		ft_printf("\n");
		commands = split_line_commands(g_21sh->line);
		i = 0;
		while (commands[i])
		{
			args = split_line_args(commands[i]);
			loop = check_cmd(args);
			free_args(args);
			free(commands[i++]);
		}
		free(commands);
		free(g_21sh->line);
	}
}

int		check_cmd(char **args)
{
	if (!args[0])
		return (1);
	handle_expansion(args);
	if (handle_builtins(args))
		return (1);
	return (exec_cmd(args));
}
