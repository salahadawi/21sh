/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:56:16 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:45:01 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_signal_suspend(void)
{
	restore_terminal_mode();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDOUT_FILENO, TIOCSTI, "\032");
}

void	handle_signal_continue(void)
{
	set_terminal_raw_mode();
	signal(SIGTSTP, handle_signal);
}

void	handle_signal_interrupt(void)
{
	free(g_21sh->line);
	g_21sh->line = ft_strnew(1);
	ft_printf("\n");
	print_shell_info();
	g_21sh->cursor.x = 0;
	save_cursor_position();
}

void	handle_signal_resize(void)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_21sh->window);
	if ((int)ft_strlen(g_21sh->line) >= g_21sh->window.ws_col *
	g_21sh->window.ws_row)
	{
		set_terminal("ho");
		set_terminal("cr");
		print_shell_info();
	}
}
