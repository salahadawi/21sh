/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:45:55 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/11 15:47:11 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	move_cursor_start(void)
{
	char *move_cursor;
	char *tmp;

	move_cursor = tgetstr("cm", NULL);
	//ft_printf("%d, %d", g_21sh->cursor.prompt_y, g_21sh->cursor.prompt_x);
	tmp = tgoto(move_cursor, g_21sh->cursor.prompt_x - 1, g_21sh->cursor.prompt_y - 1);
	tputs(tmp, 1, ft_putschar);
}

void	move_cursor_right_edge(void)
{
	int	right_moves;

	right_moves = g_21sh->window.ws_col - 1;
	set_terminal("cr");
	while (right_moves--)
		set_terminal("nd");
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