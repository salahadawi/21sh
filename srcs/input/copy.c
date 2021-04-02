/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:38:52 by jwilen            #+#    #+#             */
/*   Updated: 2021/04/02 23:28:14 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	cut_start(void)
{
	int		i;
	int		len;

	i = 0;
	g_21sh->copy_end = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	if (!(g_21sh->copy_part = ft_memalloc(g_21sh->copy_end -
	g_21sh->copy_start + 1)))
		handle_error("Malloc failed", 1);
	len = g_21sh->copy_end - g_21sh->copy_start;
	while (g_21sh->copy_start <= g_21sh->copy_end)
	{
		g_21sh->copy_part[i] = g_21sh->line[g_21sh->copy_start];
		i++;
		g_21sh->copy_start++;
	}
	g_21sh->copy_start = -1;
	cut_new_line(len);
}

void		cut(void)
{
	if (g_21sh->copy_start == -1)
	{
		free(g_21sh->copy_part);
		g_21sh->copy_start = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	}
	else
	{
		if (g_21sh->copy_start >= g_21sh->cursor.x)
			cut_start();
		else
		{
			g_21sh->copy_start = -1;
			g_21sh->copy_end = -1;
			free(g_21sh->copy_part);
		}
	}
}

static void	copy_start_alfa(void)
{
	int		i;

	i = 0;
	g_21sh->copy_end = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	if (!(g_21sh->copy_part = ft_memalloc(g_21sh->copy_end -
	g_21sh->copy_start + 1)))
		handle_error("Malloc failed", 1);
	while (g_21sh->copy_start <= g_21sh->copy_end)
	{
		g_21sh->copy_part[i] = g_21sh->line[g_21sh->copy_start];
		i++;
		g_21sh->copy_start++;
	}
	g_21sh->copy_start = -1;
}

void		copy_start(void)
{
	if (g_21sh->copy_start == -1)
	{
		free(g_21sh->copy_part);
		g_21sh->copy_start = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	}
	else
	{
		if (g_21sh->copy_start >= g_21sh->cursor.x)
			copy_start_alfa();
		else
		{
			g_21sh->copy_start = -1;
			g_21sh->copy_end = -1;
			free(g_21sh->copy_part);
		}
	}
}
