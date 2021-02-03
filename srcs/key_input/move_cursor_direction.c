/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:40:24 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/03 16:48:28 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	move_cursor_up(void)
{
	if ((int)ft_strlen(g_21sh->line) + g_21sh->cursor.x >= g_21sh->window.ws_col)
		g_21sh->cursor.x -= g_21sh->window.ws_col;
}

void	move_cursor_down(void)
{
	if (-g_21sh->cursor.x >= g_21sh->window.ws_col)
		g_21sh->cursor.x += g_21sh->window.ws_col;
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
