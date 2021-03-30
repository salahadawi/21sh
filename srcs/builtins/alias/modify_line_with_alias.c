/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_line_with_alias.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:32:00 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/29 15:11:15 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			check_while(int i)
{
	if (ft_strncmp(&g_21sh->line[i], " ", 1) != 0)
		return (1);
	else if ((ft_strnequ(&g_21sh->line[i], ";", 1) != 0))
		return (1);
	return (0);
}

void		modify_line_with_alias(void)
{
    int			i;
    int			j;
    int			k;
    char		*str;
	// char		*newstr;
    t_alias		*current;
	
	i = 0;
    j = 0;
    k = 0;
    while ((&g_21sh->line[j]) && (ft_strlen(g_21sh->line) > (size_t)j))
    {
        while(check_while(i) != 0)
        {
            i++;
            j++;
        }
        // write(1, "QQ", 2);
        if (!(str = (char*)ft_memalloc(i + 1)))
		    handle_error("Malloc failed", 1);
        ft_strncpy(str, g_21sh->line, i);
        current = g_21sh->alias;
		while (current)
		{
			if ((!ft_strcmp(str, current->alias_name)))
			{
				// if (!(newstr = (char*)ft_memalloc(ft_strlen(g_21sh->line) - i + ft_strlen(current->real_name + 2))))
				// 	handle_error("Malloc failed", 1);
				ft_memmove(&g_21sh->line[i],str, i);
				free(str);
			}
		current = current->next;
		}
        // while (k < i)
        // {
        //     str[j] = g_21sh->line[k];
        //     i--;
        // }
        // str[j] = '\0';
        ft_printf("\nSTR: %s i:%d j:%d", str, i, j);
		j++;
    }

    
}