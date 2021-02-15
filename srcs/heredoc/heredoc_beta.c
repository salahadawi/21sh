/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_beta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:23:56 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/15 14:28:27 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_delete_heredoc(char **line)
{
	*line = str_remove_char(*line, ft_strlen(*line)
	+ g_21sh->cursor_heredoc.x);
	move_cursor_right();
}

void	cursor_jump_up_heredoc(char *line, int *left_len)
{
	int	text_len;
	int	chars_skipped;

	text_len = ft_strlen("heredoc> ") + ft_strlen(line);
	if (text_len % g_21sh->window.ws_col < abs(*left_len))
	{
		while (text_len % g_21sh->window.ws_col < abs(*left_len))
		{
			chars_skipped = text_len % g_21sh->window.ws_col;
			*left_len += chars_skipped + 1;
			text_len -= chars_skipped + 1;
			set_terminal("up");
		}
		move_cursor_right_edge();
	}
}

void	find_prompt_y_heredoc(char *line)
{
	int i;

	i = g_21sh->cursor_heredoc.prompt_y + (ft_strlen("heredoc> ") +
	ft_strlen(line)) / g_21sh->window.ws_col;
	while (i-- > g_21sh->window.ws_row)
	{
		if (g_21sh->cursor_heredoc.prompt_y < 1)
			return ;
		g_21sh->cursor_heredoc.prompt_y--;
	}
}

void	move_cursor_next_line_heredoc(char *line)
{
	if (ft_strlen("heredoc> ") + (int)ft_strlen(line)
		< g_21sh->window.ws_col * g_21sh->window.ws_row)
	{
		set_terminal("do");
		set_terminal("cr");
	}
}

char	*str_add_char_heredoc(char **str, char c)
{
	int		i;
	int		index;
	char	*newstr;

	index = ft_strlen(*str) + g_21sh->cursor_heredoc.x;
	newstr = (char*)ft_memalloc(ft_strlen(*str) + 2); //protect
	i = 0;
	while (i < index)
	{
		newstr[i] = (*str)[i];
		i++;
	}
	newstr[i] = c;
	while ((*str)[i])
	{
		newstr[i + 1] = (*str)[i];
		i++;
	}
	newstr[i + 1] = '\0';
	free(*str);
	return (newstr);
}
