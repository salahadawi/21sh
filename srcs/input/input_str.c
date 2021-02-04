/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:12:41 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/02 09:49:47 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	copy_input()
{
	g_21sh->copied_input = ft_strdup(g_21sh->line);
}

void	paste_input()
{
	char *tmp;

	if (g_21sh->copied_input)
	{
		tmp = g_21sh->line;
		g_21sh->line = str_add_str(g_21sh->line, g_21sh->copied_input);
		free(tmp);
	}
}

void	print_input()
{
	int len;
	int max_len;
	int	index;

	len = g_21sh->prompt_len + ft_strlen(g_21sh->line);
	max_len = g_21sh->window.ws_col * g_21sh->window.ws_row;
	if (len > max_len)
	{
		index = 0;
		while (len - index > max_len)
			index += g_21sh->window.ws_col;
		index += g_21sh->window.ws_col - g_21sh->prompt_len;
		//len -= max_len;
		//len += g_21sh->window.ws_col;
		ft_printf("...\n%s", &g_21sh->line[index]);
	}
	else
		ft_printf("%s", g_21sh->line);
}

int		input_too_large(void)
{
	if (ft_strlen(g_21sh->line) > 100000)
	{
		free(g_21sh->line);
		ft_fprintf(2, "\nError: Input exceeds ARG_MAX.");
		g_21sh->line = ft_strdup("");
		return (1);
	}
	return (0);
}

int		get_input()
{
	if (g_debug)
		get_next_line(0, &g_21sh->line);
	else
	{
		g_21sh->line = ft_strnew(0);
		save_cursor_position();
		while (handle_keys())
		{
			
			if (input_too_large())
				break;
			move_cursor_start();
			set_terminal("cd");
			print_input();
			move_cursor();
		}
		
	}
	return (1);
}
