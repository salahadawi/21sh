/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_alfa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:04:41 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 13:25:05 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_backspace_heredoc(char **line)
{
	*line = str_remove_char_heredoc(line, ft_strlen(*line)
	+ g_21sh->cursor_heredoc.x - 1);
}

void	handle_control_sequence_heredoc(char **line, char *c)
{
	*c += 100;
	if (*c == g_21sh->key_sequences.delete_key)
		handle_delete_heredoc(line);
	else if (*c == g_21sh->key_sequences.left_arrow)
		move_cursor_left_heredoc(line);
	else if (*c == g_21sh->key_sequences.right_arrow)
		move_cursor_right_heredoc();
	else if (*c == g_21sh->key_sequences.up_arrow)
		get_history_prev_heredoc(line);
	else if (*c == g_21sh->key_sequences.down_arrow)
		get_history_next_heredoc(line);
	else if (*c == HOME)
		g_21sh->cursor_heredoc.x = -ft_strlen(*line);
	else if (*c == END)
		g_21sh->cursor_heredoc.x = 0;
	else if (*c + 10 == g_21sh->key_sequences.left_arrow)
		move_word_left_heredoc(line);
	else if (*c + 10 == g_21sh->key_sequences.right_arrow)
		move_word_right_heredoc(line);
	else if (*c + 10 == g_21sh->key_sequences.up_arrow)
		move_cursor_up_heredoc(line);//copy_input();
	else if (*c + 10 == g_21sh->key_sequences.down_arrow)
		move_cursor_down_heredoc();//paste_input();
}

void	move_cursor_heredoc(char *line)
{
	int len;

	len = g_21sh->cursor_heredoc.x;
	if ((ft_strlen("heredoc> ") + ft_strlen(line)) % g_21sh->window.ws_col == 0)
		move_cursor_next_line_heredoc(line);
	find_prompt_y_heredoc(line);
	cursor_jump_up_heredoc(line, &len);
	while (len++ < 0)
		set_terminal("le");
}

void	print_input_heredoc(char *line)
{
	int len;
	int max_len;
	int	index;

	len = ft_strlen("heredoc> ") + ft_strlen(line);
	max_len = g_21sh->window.ws_col * g_21sh->window.ws_row;
	if (len > max_len)
	{
		index = 0;
		while (len - index > max_len)
			index += g_21sh->window.ws_col;
		index += g_21sh->window.ws_col - ft_strlen("heredoc> ");
		//len -= max_len;
		//len += g_21sh->window.ws_col;
		ft_fprintf(g_21sh->stdout, "...\n%s", &line[index]);
	}
	else
		ft_fprintf(g_21sh->stdout, "%s", line);
}

void	move_cursor_start_heredoc(void)
{
	char *move_cursor;
	char *tmp;

	move_cursor = tgetstr("cm", NULL);
	//ft_printf("%d, %d", g_21sh->cursor.prompt_y, g_21sh->cursor.prompt_x);
	tmp = tgoto(move_cursor, g_21sh->cursor_heredoc.prompt_x - 1,
	g_21sh->cursor_heredoc.prompt_y - 1);
	tputs(tmp, 1, ft_putschar);
}
