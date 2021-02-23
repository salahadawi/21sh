/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:02:40 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:41:39 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_terminal(char *id)
{
	tputs(tgetstr(id, NULL), 1, ft_putschar);
}

void	restore_terminal_mode(void)
{
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->old);
	set_terminal(NORMAL_MODE);
}

void	set_terminal_raw_mode(void)
{
	g_21sh->raw.c_lflag &= ~(ECHO | ICANON);
	g_21sh->raw.c_cc[VMIN] = 0;
	g_21sh->raw.c_cc[VTIME] = 1;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw);
	set_terminal(SPECIAL_MODE);
}

void	create_terminal_raw_mode(void)
{
	tcgetattr(STDOUT_FILENO, &g_21sh->raw);
}
