/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_gamma.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:29:00 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 13:20:53 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	move_word_left_heredoc(char **line)
{
	int i;

	i = ft_strlen(*line);
	i += g_21sh->cursor_heredoc.x;
	while (i > 0)
	{
		if (ft_strchr(" \t\n\v\f\r", (*line)[i - 1]))
			move_cursor_left_heredoc(line);
		else
			break ;
		i--;
	}
	while (i > 0)
	{
		if (!ft_strchr(" \t\n\v\f\r", (*line)[i - 1]))
			move_cursor_left_heredoc(line);
		else
			break ;
		i--;
	}
}

void	get_history_next_heredoc(char **line)
{
	if (g_21sh->history)
		if (g_21sh->history->next)
		{
			free(*line);
			g_21sh->history = g_21sh->history->next;
			*line = ft_strdup(g_21sh->history->cmd);
			g_21sh->cursor_heredoc.x = 0;
		}
}

void	get_history_prev_heredoc(char **line)
{
	if (g_21sh->history)
		if (g_21sh->history->prev)
		{
			free(*line);
			g_21sh->history = g_21sh->history->prev;
			*line = ft_strdup(g_21sh->history->cmd);
			g_21sh->cursor_heredoc.x = 0;
		}
}

void	move_cursor_right_heredoc(void)
{
	if (g_21sh->cursor_heredoc.x < 0)
		g_21sh->cursor_heredoc.x++;
}

void	move_cursor_left_heredoc(char **line)
{
	if ((int)ft_strlen(*line) > -g_21sh->cursor_heredoc.x)
		g_21sh->cursor_heredoc.x--;
}
