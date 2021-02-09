/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:38:22 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/09 14:36:11 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		read_key(void)
{
	char sequence[10];

	sequence[0] = 0;
	if (read(g_21sh->stdout, sequence, 10) == -1)
		handle_error("Read failed", 1);
	if (sequence[0] == ESCAPE)
	{
		if (sequence[1] == '[')
		{
			if (sequence[2] == '1')
				return (sequence[5] - 110);
			return (sequence[2] - 100);
		}
	}
	return (sequence[0]);
}

char	*str_remove_char(char *str, int index)
{
	int		i;
	char	*newstr;

	if (index < 0 || index >= (int)ft_strlen(str))
		return (str);
	if (!(newstr = (char*)ft_memalloc(ft_strlen(str))))
		handle_error("Malloc failed", 1);
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	if (!str[i])
	{
		free(str);
		return (newstr);
	}
	while (str[i + 1])
	{
		newstr[i] = str[i + 1];
		i++;
	}
	newstr[i] = '\0';
	free(str);
	return (newstr);
}


char	*str_add_paste(char *str, char *paste)
{
	int		i;
	int 	j;
	int		index;
	char	*newstr;
	index = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	// ft_printf("%d\n", ft_strlen(str) + ft_strlen(g_21sh->copy_part) + 1);
	// ft_printf("%d\n", ft_strlen(paste));
	// while(1)
	// 	i =1;
	if (!(newstr = (char*)ft_memalloc(ft_strlen(str) + ft_strlen(paste) + 2)))
		handle_error("Malloc failed", 1);
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	j = 0;
	while (paste[j])
	{
		newstr[i] = paste[j];
		i++;
		j++;
	}
	while (str[i-j])
	{
		newstr[i] = str[i-j];
		i++;
	}
	newstr[i] = '\0';
	free(str);
	return (newstr);

}

char	*str_add_char(char *str, char c)
{
	int		i;
	int		index;
	char	*newstr;

	index = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	if (!(newstr = (char*)ft_memalloc(ft_strlen(str) + 2)))
		handle_error("Malloc failed", 1);
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	while (str[i])
	{
		newstr[i + 1] = str[i];
		i++;
	}
	newstr[i + 1] = '\0';
	free(str);
	return (newstr);
}

void	handle_delete(void)
{
	g_21sh->line = str_remove_char(g_21sh->line, ft_strlen(g_21sh->line)
	+ g_21sh->cursor.x);
	move_cursor_right();
}
