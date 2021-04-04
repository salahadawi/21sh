/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:02:11 by jwilen            #+#    #+#             */
/*   Updated: 2021/04/03 00:25:41 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			paste(void)
{
	if (g_21sh->copy_start <= g_21sh->copy_end)
		g_21sh->line = str_add_paste(g_21sh->line, g_21sh->copy_part);
}

static char		*cut_str(int index, char *newstr,
			char *str, int len)
{
	int		i;
	int		j;

	i = 0;
	while (i < (index - len))
	{
		newstr[i] = str[i];
		i++;
	}
	j = i;
	i = len + i;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[i] = '\0';
	return (newstr);
}

static char		*str_cut(char *str, int len)
{
	int		index;
	char	*newstr;

	index = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	if (!(newstr = (char*)ft_memalloc(ft_strlen(str) - (len - 1))))
		handle_error("Malloc failed", 1);
	newstr = cut_str(index, newstr, str, len);
	free(str);
	return (newstr);
}

void			cut_new_line(int len)
{
	if (g_21sh->copy_start <= g_21sh->copy_end)
		g_21sh->line = str_cut(g_21sh->line, len);
}
