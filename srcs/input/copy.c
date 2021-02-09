/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:38:52 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/09 12:01:09 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void        copy_start()
{
    int		i;
	
	i = 0;
    if (!g_21sh->copy_start)
        g_21sh->copy_start =  ft_strlen(g_21sh->line) + g_21sh->cursor.x;
    else
	{
		g_21sh->copy_end = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
		g_21sh->copy_part = ft_memalloc(g_21sh->copy_end - g_21sh->copy_start + 1);
		while(g_21sh->copy_start <= g_21sh->copy_end)
		{
			g_21sh->copy_part[i] = g_21sh->line[g_21sh->copy_start];
			i++;
			g_21sh->copy_start++;
		}
	}
}