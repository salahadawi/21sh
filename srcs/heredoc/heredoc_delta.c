/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:04:58 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/05 12:19:04 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_nbrlen(int nbr)
{
	int i;

	i = 0;
	while (nbr || !i)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*str_remove_char_heredoc(char **str, int index)
{
	int		i;
	char	*newstr;

	if (index < 0 || index >= (int)ft_strlen(*str))
		return (*str);
	if (!(newstr = (char*)ft_memalloc(ft_strlen(*str))))
		handle_error("Malloc failed", 1);
	i = 0;
	while (i++ < index)
		newstr[i] = (*str)[i];
	if (!(*str)[i])
	{
		free(*str);
		return (newstr);
	}
	while ((*str)[i + 1])
	{
		newstr[i] = (*str)[i + 1];
		i++;
	}
	newstr[i] = '\0';
	free(*str);
	return (newstr);
}

void	move_cursor_up_heredoc(char **line)
{
	if ((int)ft_strlen(*line) + g_21sh->cursor_heredoc.x >=
	g_21sh->window.ws_col)
		g_21sh->cursor_heredoc.x -= g_21sh->window.ws_col;
}

void	move_cursor_down_heredoc(void)
{
	if (-g_21sh->cursor_heredoc.x >= g_21sh->window.ws_col)
		g_21sh->cursor_heredoc.x += g_21sh->window.ws_col;
}

void	move_word_right_heredoc(char **line)
{
	int i;
	int len;

	len = ft_strlen(*line);
	i = len;
	i += g_21sh->cursor_heredoc.x;
	while (i < len)
	{
		if (!ft_strchr(" \t\n\v\f\r", (*line)[i]))
			move_cursor_right_heredoc();
		else
			break ;
		i++;
	}
	while (i < len)
	{
		if (ft_strchr(" \t\n\v\f\r", (*line)[i]))
			move_cursor_right_heredoc();
		else
			break ;
		i++;
	}
}
