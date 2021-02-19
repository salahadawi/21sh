/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:20:43 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/19 10:30:31 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		input_too_large_heredoc(char **line)
{
	if (ft_strlen(*line) > 100000)
	{
		free(*line);
		ft_fprintf(2, "\nError: Input exceeds ARG_MAX.");
		*line = ft_strdup("");
		return (1);
	}
	return (0);
}

int		handle_keys_heredoc(char **line, char *previous_pressed_key)
{
	char c;

	c = read_key();
	if (c == 0)
		return (1);
	if (c < 0)
	{
		handle_control_sequence_heredoc(line, &c);
		return (1);
	}
	if (c == BACKSPACE)
		handle_backspace_heredoc(line);
	else if (c == ENTER)
		return (0);
	else if (c == TAB)
		autocomplete(line, *previous_pressed_key);
	else if (c == 4) // CTRL + D
	{
		//restore_terminal_mode();
		return (-1); //temporary, need to restore terminal and free memory here
	}
	else if (ft_isprint(c))
		*line = str_add_char_heredoc(line, c);
	*previous_pressed_key = c;
	return (1);
}

void	save_cursor_position_heredoc(void)
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_fprintf(g_21sh->stdout, "%s", "\x1b[6n");
	ft_bzero(sequence, 100);
	read(g_21sh->stdin, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 97)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 + ft_nbrlen(y) < 100 ?
	i + 2 + ft_nbrlen(y) : 0]);
	g_21sh->cursor_heredoc.prompt_y = y ? y : g_21sh->cursor_heredoc.prompt_y;
	g_21sh->cursor_heredoc.prompt_x = x ? x : g_21sh->cursor_heredoc.prompt_x;// + g_21sh->prompt_len;
	//ft_printf("%s", &sequence[i]);
}

int		get_heredoc_input(char **line)
{
	char	previous_pressed_key;
	int		value;

	*line = ft_strnew(0);
	save_cursor_position_heredoc();
	while ((value = handle_keys_heredoc(line, &previous_pressed_key)) > 0)
	{
		//should not exit from child process, instead find some way to return 0 here
		if (input_too_large_heredoc(line))
			break ;
		move_cursor_start_heredoc();
		set_terminal("cd");
		print_input_heredoc(*line);
		move_cursor_heredoc(*line);
	}
	if (value == -1)
		return (0);
	return (1);
}

void	redirect_heredoc_to_input(char *eof)
{
	char	*line;
	int		fd;

	tcsetattr(g_21sh->stdout, TCSAFLUSH, &g_21sh->raw);
	g_21sh->cursor_heredoc.prompt_x = g_21sh->cursor_heredoc.prompt_x + 1;
	g_21sh->cursor_heredoc.prompt_y = g_21sh->cursor_heredoc.prompt_y + 1;
	if ((fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		handle_error("Open failed", 1);
	ft_fprintf(g_21sh->stdout, "heredoc> ");
	while (get_heredoc_input(&line))
	{
		if (ft_strequ(line, eof))
			break ;
		ft_putendl_fd(line, fd); // write to tmp file
		free(line);
		ft_fprintf(g_21sh->stdout, "\nheredoc> ");
	}
	free(line);
	ft_fprintf(g_21sh->stdout, "\n");
	close(fd);
	fd = open(".heredoc.tmp", O_RDONLY);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
}
