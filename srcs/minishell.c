/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/11 17:14:16 by jwilen           ###   ########.fr       */
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

int		ft_nbrlen(int nbr)
{
	int i;

	i = 0;
	while (nbr || !i)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *x, int *y)
{
	char	sequence[100];
	int		i;

	ft_printf("%s", "\x1b[6n");
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 100)
		i++;
	*y = ft_atoi(&sequence[i + 1]);
	*x = ft_atoi(&sequence[i + 2 + ft_nbrlen(*y)]);
}

void	cursor_jump_up(int *left_len)
{
	int	text_len;
	int	chars_skipped;

	text_len = g_21sh->prompt_len + ft_strlen(g_21sh->line);
	if (text_len % g_21sh->window.ws_col < abs(*left_len))
	{
		while (text_len % g_21sh->window.ws_col < abs(*left_len))
		{
			chars_skipped = text_len % g_21sh->window.ws_col;
			*left_len += chars_skipped + 1;
			text_len -= chars_skipped + 1;
			set_terminal("up");
		}
		move_cursor_right_edge();
	}
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

void	save_cursor_position()
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_printf("%s", "\x1b[6n");
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 100)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 + ft_nbrlen(y)]);
	g_21sh->cursor.prompt_y = y ? y : g_21sh->cursor.prompt_y;
	g_21sh->cursor.prompt_x = x ? x : g_21sh->cursor.prompt_x;// + g_21sh->prompt_len;
	//ft_printf("%s", &sequence[i]);
}

void	loop_shell(void)
{
	char	**commands;
	char	**args;
	int		loop;
	int		i;
	t_tok	*current;

	loop = 1;
	get_history_file_path();
	while (loop)
	{
		open_history_file();
		g_21sh->cursor.x = 0;
		//set_terminal(NORMAL_MODE);
		print_shell_info();
		if (get_input() < 1)
			break ;
		save_command_history();
		lexi();
		check_cmd();
		free_history();
		// free(commands);
		free(g_21sh->line);
		set_terminal(SPECIAL_MODE);
	}
}

int		check_cmd()
{
		t_tok	*current;
		
		current = g_21sh->token;
		while (current)
		{
			ft_printf("\ntokens: %s\n", current->str);
			current = current->next;
		}
	if (!g_21sh->token)
		return (1);
	handle_expansion();
	run_first();
	return (0);
}
