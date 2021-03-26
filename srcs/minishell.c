/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/26 21:34:00 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
static void		init_alias(void)
{
	t_alias		*head;

	g_21sh->alias = NULL;
	head = g_21sh->alias;
	g_21sh->head_alias = g_21sh->alias;
}	
void			loop_shell(void)
{
	int		loop;

	loop = 1;
	get_history_file_path();
	init_alias();
	while (loop)
	{
		open_history_file();
		g_21sh->cursor.x = 0;
		print_shell_info();
		get_autocomplete_commands();
		if (get_input() < 1)
			break ;
		save_command_history();
		if (lexi() == 0)
		{
			ft_printf("\n");
			handle_expansion();
			run_commands();
			move_cursor_newline();
		}
		free_history();
		// free_alias();
		free(g_21sh->line);
	}
}
