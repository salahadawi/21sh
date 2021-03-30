/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:53:26 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/30 09:01:04 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_history_prev(void)
{
	if (g_21sh->history)
		if (g_21sh->history->prev)
		{
			free(g_21sh->line);
			g_21sh->history = g_21sh->history->prev;
			g_21sh->line = ft_strdup(g_21sh->history->cmd);
			g_21sh->cursor.x = 0;
		}
}

void	get_history_next(void)
{
	if (g_21sh->history)
		if (g_21sh->history->next)
		{
			free(g_21sh->line);
			g_21sh->history = g_21sh->history->next;
			g_21sh->line = ft_strdup(g_21sh->history->cmd);
			g_21sh->cursor.x = 0;
		}
}
