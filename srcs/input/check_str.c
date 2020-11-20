/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 06:49:18 by jochumwilen       #+#    #+#             */
/*   Updated: 2020/11/20 10:06:05 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				check_str(void)
{
    int     i;
    char    *str;
    int     k[ft_strlen(g_21sh->line)];

    i = 0;
    str = g_21sh->line;
    while (*str)
    {
        if (*str == '"')
            k[++i] = *str;
    }
    str++;

}