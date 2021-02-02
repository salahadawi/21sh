/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:54:31 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/02 12:49:42 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	restore_signals(void)
{
	int i;

	i = 0;
	while (i <= SIGRTMAX)
		signal(i++, SIG_DFL);
}

void	handle_signal(int sig)
{
	if (sig == SIGTSTP)
		handle_signal_suspend();
	else if (sig == SIGCONT)
		handle_signal_continue();
	else if (sig == SIGINT)
		handle_signal_interrupt();
	else if (sig == SIGWINCH)
		handle_signal_resize();
	else
	{
		restore_terminal_mode();
		//free_memory(g_select);
		exit(0);
	}
}

void	init_signal_handling(void)
{
	int i;

	i = 0;
	while (i <= SIGRTMAX)
		signal(i++, handle_signal);
}
