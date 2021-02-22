/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_alfa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:20:20 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/22 11:24:36 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_backspace(void)
{
	g_21sh->line = str_remove_char(g_21sh->line, ft_strlen(g_21sh->line)
	+ g_21sh->cursor.x - 1);
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
		move_cursor_up();//copy_input();
	else if (*c + 10 == g_21sh->key_sequences.down_arrow)
		move_cursor_down();//paste_input();
}
