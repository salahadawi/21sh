/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:42:11 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/11 15:42:35 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	move_word_left(void)
{
	int i;

	i = ft_strlen(g_21sh->line);
	i += g_21sh->cursor.x;
	while (i > 0)
	{
		if (ft_strchr(" \t\n\v\f\r", g_21sh->line[i - 1]))
			move_cursor_left();
		else
			break;
		i--;
	}
	while (i > 0)
	{
		if (!ft_strchr(" \t\n\v\f\r", g_21sh->line[i - 1]))
			move_cursor_left();
		else
			break;
		i--;
	}
}

void	move_word_right(void)
{
	int i;
	int len;

	len = ft_strlen(g_21sh->line);
	i = len;
	i += g_21sh->cursor.x;
	while (i < len)
	{
		if (!ft_strchr(" \t\n\v\f\r", g_21sh->line[i]))
			move_cursor_right();
		else
			break;
		i++;
	}
	while (i < len)
	{
		if (ft_strchr(" \t\n\v\f\r", g_21sh->line[i]))
			move_cursor_right();
		else
			break;
		i++;
	}
}