/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:00:00 by jwilen            #+#    #+#             */
/*   Updated: 2021/04/02 15:34:31 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_putschar(int c)
{
	if (write(g_21sh->stdout, &c, 1) == -1)
		return (-1);
	return (0);
}

void	init_termcaps(void)
{
	char *terminal_name;

	if (!(isatty(0)))
		handle_error("Not a terminal", 0);
	if (!(terminal_name = getenv("TERM")))
		handle_error("Terminal enviroment variable not found", 0);
	if (tgetent(NULL, terminal_name) < 1)
		handle_error("Terminal specified in env not found", 0);
	init_key_sequences();
	tcgetattr(STDOUT_FILENO, &g_21sh->old);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_21sh->window);
}
