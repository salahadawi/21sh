/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/02 19:55:45 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	loop_shell(void)
{
	int		loop;

	loop = 1;
	get_history_file_path();
	while (loop)
	{
		open_history_file();
		g_21sh->cursor.x = 0;
		print_shell_info();
		get_autocomplete_commands();
		if (get_input() < 1)
			break ;
		save_command_history();
		lexi();
		ft_printf("\n");
		handle_expansion();
		run_commands();
		move_cursor_newline();
		free_history();
		free(g_21sh->line);
	}
}
