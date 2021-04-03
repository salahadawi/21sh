/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:43:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/04/02 22:10:42 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	handle_keys_c(char c)
{
	if (c == BACKSPACE)
		handle_backspace();
	else if (c == CTRL_K && ft_strlen(g_21sh->line) > 0)
		copy_start();
	else if (c == CTRL_U && ft_strlen(g_21sh->line) > 0)
		cut();
	else if (c == CTRL_P)
		paste();
	else if (c == CTRL_D && !ft_strlen(g_21sh->line))
	{
		restore_terminal_mode();
		builtin_exit(&g_21sh->line);
	}
	else if (ft_isprint(c))
		g_21sh->line = str_add_char(g_21sh->line, c);
	g_21sh->previous_pressed_key = c;
}

int			handle_keys(void)
{
	char c;

	c = read_key();
	if (c == 0)
		return (1);
	if (c < 0)
	{
		handle_control_sequence(&c);
		return (1);
	}
	else if (c == ENTER)
		return (0);
	handle_keys_c(c);
	return (1);
}
