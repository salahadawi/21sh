/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2020/05/07 13:18:50 by sadawi           ###   ########.fr       */
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
		{
			if (sequence[2] == '1')
				return (sequence[5] - 110);
			return (sequence[2] - 100);
		}
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

void	get_history_prev(void)
{
	if (g_21sh->history)
		if (g_21sh->history->prev)
		{
			free(g_21sh->line);
			g_21sh->history = g_21sh->history->prev;
			g_21sh->line = ft_strdup(g_21sh->history->cmd);
		}
}

void	get_history_next(void)
{
	if (g_21sh->history)
		if (g_21sh->history->next)
		{
			free(g_21sh->line);
			g_21sh->history = g_21sh->history->next;
			g_21sh->line = ft_strdup(g_21sh->history->cmd);
		}
}

void	move_word_left(void)
{
	int i;

	i = ft_strlen(g_21sh->line);
	i += g_21sh->cursor.x;
	while (i > 0)
	{
		if (ft_strchr(" \t\n\v\f\r", g_21sh->line[i - 1]))
			move_cursor_left();
		else
			break;
		i--;
	}
	while (i > 0)
	{
		if (!ft_strchr(" \t\n\v\f\r", g_21sh->line[i - 1]))
			move_cursor_left();
		else
			break;
		i--;
	}
}

void	move_word_right(void)
{
	int i;
	int len;

	len = ft_strlen(g_21sh->line);
	i = len;
	i += g_21sh->cursor.x;
	while (i < len)
	{
		if (!ft_strchr(" \t\n\v\f\r", g_21sh->line[i]))
			move_cursor_right();
		else
			break;
		i++;
	}
	while (i < len)
	{
		if (ft_strchr(" \t\n\v\f\r", g_21sh->line[i]))
			move_cursor_right();
		else
			break;
		i++;
	}
}

void	copy_input()
{
	g_21sh->copied_input = ft_strdup(g_21sh->line);
}

void	paste_input()
{
	char *tmp;

	if (g_21sh->copied_input)
	{
		tmp = g_21sh->line;
		g_21sh->line = ft_strjoin(g_21sh->line, g_21sh->copied_input);
		free(tmp);
	}
}

void	handle_control_sequence(char *c)
{
	*c += 100;
	
	if (*c == g_21sh->key_sequences.delete_key)
		handle_delete();
	else if (*c == g_21sh->key_sequences.left_arrow)
		move_cursor_left();
	else if (*c == g_21sh->key_sequences.right_arrow)
		move_cursor_right();
	else if (*c == g_21sh->key_sequences.up_arrow)
		get_history_prev();
	else if (*c == g_21sh->key_sequences.down_arrow)
		get_history_next();
	else if (*c == HOME)
		g_21sh->cursor.x = -ft_strlen(g_21sh->line);
	else if (*c == END)
		g_21sh->cursor.x = 0;
	else if (*c + 10 == g_21sh->key_sequences.left_arrow)
		move_word_left();
	else if (*c + 10 == g_21sh->key_sequences.right_arrow)
		move_word_right();
	else if (*c + 10 == g_21sh->key_sequences.up_arrow)
		copy_input();
	else if (*c + 10 == g_21sh->key_sequences.down_arrow)
		paste_input();
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
	{
		restore_terminal_mode();
		exit(0); //temporary, need to restore terminal and free memory here
	}
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

void	get_cursor_position(int *x, int *y)
{
	char	sequence[100];
	int		i;

	ft_printf("%s", "\x1b[6n");
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 100)
		i++;
	*y = ft_atoi(&sequence[i + 1]);
	*x = ft_atoi(&sequence[i + 2 + ft_nbrlen(*y)]);
}

void	move_cursor_right_edge(void)
{
	int	right_moves;

	right_moves = g_21sh->window.ws_col - 1;
	set_terminal("cr");
	while (right_moves--)
		set_terminal("nd");
}

void	cursor_jump_up(int *left_len)
{
	int	text_len;
	int	chars_skipped;

	text_len = g_21sh->prompt_len + ft_strlen(g_21sh->line);
	if (text_len % g_21sh->window.ws_col < abs(*left_len))
	{
		while (text_len % g_21sh->window.ws_col < abs(*left_len))
		{
			chars_skipped = text_len % g_21sh->window.ws_col;
			*left_len += chars_skipped + 1;
			text_len -= chars_skipped + 1;
			set_terminal("up");
		}
		move_cursor_right_edge();
	}
}

void	move_cursor_next_line(void)
{
	if (g_21sh->prompt_len + (int)ft_strlen(g_21sh->line)
		< g_21sh->window.ws_col * g_21sh->window.ws_row)
	{
		set_terminal("do");
		set_terminal("cr");
	}
}

void	find_prompt_y(void)
{
	int i;

	i = g_21sh->cursor.prompt_y + (g_21sh->prompt_len + ft_strlen(g_21sh->line))
	 / g_21sh->window.ws_col;
	while (i-- > g_21sh->window.ws_row)
		g_21sh->cursor.prompt_y--;
}

void	move_cursor(void)
{
	int len;

	len = g_21sh->cursor.x;
	if ((g_21sh->prompt_len + ft_strlen(g_21sh->line)) % g_21sh->window.ws_col == 0)
		move_cursor_next_line();
	find_prompt_y();
	cursor_jump_up(&len);
	while (len++ < 0)
		set_terminal("le");
}

void	save_cursor_position()
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_printf("%s", "\x1b[6n");
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 100)
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
	save_cursor_position();
	while (handle_keys())
	{
		move_cursor_start();
		set_terminal("cd");
		ft_printf("%s", g_21sh->line);
		move_cursor();
	}
	return (1);
}

t_history	*new_history_node(char *line, t_history *prev)
{
	t_history *node;

	node = (t_history*)ft_memalloc(sizeof(t_history));
	node->cmd = line;
	node->prev = prev;
	node->next = NULL;
	return (node);
}

void	add_to_history(char *line)
{
	if (!g_21sh->history)
		g_21sh->history = new_history_node(line, NULL);
	else
	{
		g_21sh->history->next = new_history_node(line, g_21sh->history);
		g_21sh->history = g_21sh->history->next;
	}
}

void	open_history_file(void)
{
	char *line;

	g_21sh->history = NULL;
	g_21sh->history_fd = open(".21sh_history", O_RDWR | O_APPEND | O_CREAT, 0666);
	if (g_21sh->history_fd == -1)
		return ;
	while (get_next_line(g_21sh->history_fd, &line) > 0)
		add_to_history(line);
	add_to_history(ft_strdup(""));
}

int		same_as_previous_command()
{
	if (g_21sh->history->prev)
		g_21sh->history = g_21sh->history->prev;
	while (g_21sh->history->next->next)
		g_21sh->history = g_21sh->history->next;
	if (ft_strequ(g_21sh->line, g_21sh->history->cmd))
		return (1);
	return (0);
}

int		input_just_whitespace(void)
{
	int i;

	i = 0;
	while (g_21sh->line[i])
		if (!ft_strchr(" \t\n\v\f\r",g_21sh->line[i++]))
			return (0);
	return (1);
}

void	save_command_history(void)
{
	if (g_21sh->history_fd != -1)
		if (!same_as_previous_command() && !input_just_whitespace())
			ft_putendl_fd(g_21sh->line, g_21sh->history_fd);
}

void	free_history(void)
{
	t_history *tmp;
	if (!g_21sh->history)
		return ;
	while (g_21sh->history->prev)
		g_21sh->history = g_21sh->history->prev;
	while (g_21sh->history)
	{
		tmp = g_21sh->history->next;
		free(g_21sh->history->cmd);
		free(g_21sh->history);
		g_21sh->history = tmp;
	}
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
		open_history_file();
		g_21sh->cursor.x = 0;
		print_shell_info();
		if (get_input() < 1)
			break ;
		save_command_history();
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
		free_history();
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
