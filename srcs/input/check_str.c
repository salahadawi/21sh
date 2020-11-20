/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 06:49:18 by jochumwilen       #+#    #+#             */
/*   Updated: 2020/11/20 14:54:25 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

# define MATCH(a,b) ((a== ')' && b == '(') || (a == ']' && b == '[') || (a == '}' && b == '{'))

int		brackets(char *str)
{
	int i = 0;
	int store[ft_strlen(str)];

	while (*str)
	{
		if (*str == '{' || *str == '(' || *str == '[')
			store[++i] = *str;
		else if (*str == '}' || *str == ')' || *str == ']')
		{
			if (MATCH(*str, store[i]) == 0)
				return (*str);
			--i;
		}
		str++;
	}
	if (i != 0)
		return (store[i]);
	return (0);
}

// int			main(int ac, char **av)
// {
// 	int i = 1;

// 	if (ac < 2)
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	while (ac > i)
// 	{
// 		if (brackets(av[i]) == -1)
// 			write(1, "Error\n", 6);
// 		if (brackets(av[i]) == 0)
// 			write(1, "OK\n", 3);
// 		i++;
// 	}
// 	return (0);
// }

char                *add_quote(char seek, char *str)
{
    char    *new_str;
    
    seek == QSTRING ? ft_printf("quote> ") : ft_printf("dquote> ");
    move_cursor_down();
    g_21sh->read_more = str;
    // new_str = ft_strjoin(g_21sh->read_more, g_21sh->line);
    ft_printf("\nn1: %s", g_21sh->read_more);
    get_input();
    new_str = ft_strjoin(g_21sh->read_more, g_21sh->line);
    // free(new_str);
    ft_printf("\nn2: %s", new_str);
    return (new_str);

}

void				check_str(void)
{
    char    *str;
    char    seek;
    int     len;

    str = g_21sh->line;
    while (*str)
    {
        if (*str == '"' || *str == '\'')
        {
            seek = *str;
            str++;
            while (*str != seek)
            {
                if (*str == seek)
                {
                    seek = '\0';
                    break;
                }
                if (*str == '\0')
                {
                    len = ft_strlen(str);
                    while (str[len -1] != seek)
                    {
                        ft_printf(" %c %d \n", seek, len);
                        str = add_quote(seek, str);
                        len = ft_strlen(str);
                    }
                    break ;
                }
                str++;
            }
        }
        str++;    }
}