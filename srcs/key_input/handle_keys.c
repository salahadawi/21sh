/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:43:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/04 22:05:55 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	handle_keys_c(char c)
{
	if (c == BACKSPACE)
		handle_backspace();
	else if (c == 11 && ft_strlen(g_21sh->line) > 0)  // Ctrl + k
		copy_start();
	else if (c == 16)
		paste();
	else if (c == TAB)
		autocomplete(&g_21sh->line, g_21sh->previous_pressed_key);
	else if (c == 4 && !ft_strlen(g_21sh->line)) // CTRL + D
	{
		restore_terminal_mode();
		exit(0); //temporary, need to restore terminal and free memory here
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
