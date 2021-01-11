/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 06:49:18 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/01/10 20:10:33 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				ask_for_more(char *str, int i, char mark)
{
	while (str[i] != mark)
	{
		if (str[i] == '\0')
		{
			mark == '\"' ? ft_printf("\ndquote>\n") : ft_printf("\nquote>\n");
			save_cursor_position();
			while (handle_keys())
			{
				if (input_too_large())
					break;
				// move_cursor_start();
				set_terminal("cd");
				print_input();
				move_cursor();
				
				
			}
			// break;
		}
		i++;
	}
	return (i);

}


void				check_str(void)
{
    char    *str;
	char	mark;
	int		i;

	i = 0;
    str = g_21sh->line;
    while (str[i])
    {
        if (str[i] == '\"')
		{
			mark = '\"';
			i++;
			i= ask_for_more(str, i, mark);
		}
		else if (str[i] == '\'')
		{
			mark = '\'';
			i++;
			i = ask_for_more(str, i, mark);
		}
		i++;
    }
}