/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:54:31 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/04 21:10:37 by sadawi           ###   ########.fr       */
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
		;//handle_signal_suspend();
	else if (sig == SIGCONT)
		handle_signal_continue();
	else if (sig == SIGINT)
		handle_signal_interrupt();
	else if (sig == SIGWINCH)
		handle_signal_resize();
	else
	{
		;
	}
}

void	init_signal_handling(void)
{
	int i;

	i = 0;
	signal(SIGTSTP, handle_signal);
	signal(SIGCONT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGWINCH, handle_signal);
}
