/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:43:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/01/11 15:31:29 by sadawi           ###   ########.fr       */
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

int		handle_keys(void)
{
	char c;

	c = read_key();
	// ft_printf("%d", c);
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
	else if (c == 9)
		exit(2);//ft_printf("TAB");
	else if (c == 4)
	{
		restore_terminal_mode();
		exit(0); //temporary, need to restore terminal and free memory here
	}
	else if (ft_isprint(c))
		g_21sh->line = str_add_char(g_21sh->line, c);
	return (1);
}