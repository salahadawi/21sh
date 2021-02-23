/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:44:21 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:52:10 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*str_add_str(char *str, char *str2)
{
	int		i;
	int		index;
	char	*newstr;

	index = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	newstr = (char*)ft_memalloc(ft_strlen(str) + ft_strlen(str2) + 1);
	!newstr ? exit(1) : 0;
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	ft_strcat(newstr, str2);
	while (str[i])
	{
		newstr[i + ft_strlen(str2)] = str[i];
		i++;
	}
	newstr[i + ft_strlen(str2)] = '\0';
	return (newstr);
}

void	find_prompt_y(void)
{
	int i;

	i = g_21sh->cursor.prompt_y + (g_21sh->prompt_len + ft_strlen(g_21sh->line))
	/ g_21sh->window.ws_col;
	while (i-- > g_21sh->window.ws_row)
	{
		if (g_21sh->cursor.prompt_y < 1)
			return ;
		g_21sh->cursor.prompt_y--;
	}
}

int		*get_pipes(t_command *commands)
{
	int		*pipes;
	size_t	pipe_amount;
	size_t	i;

	pipe_amount = (commands_amount(commands) - 1) * 2;
	if (!pipe_amount)
		return (NULL);
	pipes = (int*)ft_memalloc(sizeof(int) * (pipe_amount + 1));
	i = 0;
	while (i < pipe_amount)
	{
		pipe(&(pipes[i]));
		i += 2;
	}
	pipes[i] = -1;
	return (pipes);
}
