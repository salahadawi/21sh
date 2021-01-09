/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 06:49:18 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/01/09 23:09:11 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				check_str(void)
{
    int     i;
    int		quote;
    char    *str;
    int     k[ft_strlen(g_21sh->line)];


    i = 0;
	quote = 0;
    str = g_21sh->line;
    //ft_printf("string: %s\n", str);
    while (str[i])
    {
        if (str[i] == '\"')
			quote++;
		i++;

    }
	ft_printf("\nquote: %d\n", quote);

}