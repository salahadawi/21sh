/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 09:15:16 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:50:22 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	save_cursor_position(void)
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_printf("%s", "\x1b[6n");
	ft_bzero(sequence, 100);
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 97)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 +
	ft_nbrlen(y) < 100 ? i + 2 + ft_nbrlen(y) : 0]);
	g_21sh->cursor.prompt_y = y ? y : g_21sh->cursor.prompt_y;
	g_21sh->cursor.prompt_x = x ? x : g_21sh->cursor.prompt_x;
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

void	move_cursor_newline(void)
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_printf("%s", "\x1b[6n");
	ft_bzero(sequence, 100);
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 97)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 + ft_nbrlen(y) < 100 ?
	i + 2 + ft_nbrlen(y) : 0]);
	if (x > 1)
	{
		set_terminal(TEXT_INVERSE_VIDEO);
		ft_printf("%%");
		set_terminal(TEXT_NORMAL);
		ft_printf("\n");
	}
}
