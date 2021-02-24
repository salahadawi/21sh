/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:38:52 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/24 08:59:19 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		copy_start(void)
{
	int		i;

	i = 0;
	if (g_21sh->copy_start == -1)
		g_21sh->copy_start = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	else
	{
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
}
