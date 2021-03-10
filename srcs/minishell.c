/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/10 15:36:25 by sadawi           ###   ########.fr       */
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
			break ; //never breaks???
		save_command_history();
		lexi();

		//for (t_token *cur = g_21sh->token; cur; cur = cur->next)
			//ft_printf("\ntoken: %d %s\n", cur->type, cur->value);

		ft_printf("\n");
		handle_expansion();
		run_commands();
		move_cursor_newline(); //if output didn't end with newline
		free_history();
		free(g_21sh->line); //jwi
	}
}

// int		check_cmd(void)
// {
// 	run_first();
// 	return (0);
// }
