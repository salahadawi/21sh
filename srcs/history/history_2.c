/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:52:20 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/30 08:58:39 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_history	*new_history_node(char *line, t_history *prev)
{
	t_history *node;

	if (!(node = (t_history*)ft_memalloc(sizeof(t_history))))
		handle_error("Malloc failed", 1);
	node->cmd = line;
	node->prev = prev;
	node->next = NULL;
	return (node);
}

void		add_to_history(char *line)
{
	if (!g_21sh->history)
		g_21sh->history = new_history_node(line, NULL);
	else
	{
		g_21sh->history->next = new_history_node(line, g_21sh->history);
		g_21sh->history = g_21sh->history->next;
	}
}

int			same_as_previous_command(void)
{
	if (g_21sh->history->prev)
		g_21sh->history = g_21sh->history->prev;
	if (g_21sh->history->next)
	{
		while (g_21sh->history->next->next)
			g_21sh->history = g_21sh->history->next;
	}
	if (ft_strequ(g_21sh->line, g_21sh->history->cmd))
		return (1);
	return (0);
}

void		free_history(void)
{
	t_history *tmp;

	if (!g_21sh->history)
		return ;
	while (g_21sh->history->prev)
		g_21sh->history = g_21sh->history->prev;
	while (g_21sh->history)
	{
		tmp = g_21sh->history->next;
		free(g_21sh->history->cmd);
		free(g_21sh->history);
		g_21sh->history = tmp;
	}
}
