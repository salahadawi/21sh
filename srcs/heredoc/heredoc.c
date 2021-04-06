/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:20:43 by jwilen            #+#    #+#             */
/*   Updated: 2021/04/06 19:49:48 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		input_too_large_heredoc(char **line)
{
	if (ft_strlen(*line) > ARG_MAX)
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
	else if (c == CTRL_D)
		return (-1);
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
	g_21sh->cursor_heredoc.prompt_x = x ? x : g_21sh->cursor_heredoc.prompt_x;
}

int		get_heredoc_input(char **line)
{
	char	previous_pressed_key;
	int		value;

	*line = ft_strnew(0);
	save_cursor_position_heredoc();
	while ((value =
	handle_keys_heredoc(line, &previous_pressed_key)) > 0)
	{
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
	signal(SIGINT, SIG_IGN);
	while (get_heredoc_input(&line))
	{
		if (ft_strequ(line, eof))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
		ft_fprintf(g_21sh->stdout, "\nheredoc> ");
	}
	signal(SIGINT, handle_signal);
	free(line);
	ft_fprintf(g_21sh->stdout, "\n");
	close(fd);
	fd = open(".heredoc.tmp", O_RDONLY);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
}
