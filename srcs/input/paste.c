/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:02:11 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/05 12:25:01 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			paste(void)
{
	if (g_21sh->copy_start <= g_21sh->copy_end)
		g_21sh->line = str_add_paste(g_21sh->line, g_21sh->copy_part);
}
