/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/18 10:59:56 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	loop_shell(void)
{
	char	**commands;
	char	**args;
	int		loop;
	int		i;
	t_token	*current;

	loop = 1;
	get_history_file_path();
	while (loop)
	{
		open_history_file();
		g_21sh->cursor.x = 0;
		//set_terminal(NORMAL_MODE);
		print_shell_info();
		get_autocomplete_commands();
		if (get_input() < 1)
		{
			break ; //never breaks???
		}
		save_command_history();
		lexi();
		current = g_21sh->token; 
		ft_printf("\n");
		handle_expansion();
		run_commands();
		move_cursor_newline(); //if output didn't end with newline
		//check_cmd(); // write somekind of ast tree or grammar, then execute commands
		
		free_history();
		// free(commands);
		free(g_21sh->line);
		//set_terminal(SPECIAL_MODE); //what is this for??
	}
}

int		check_cmd()
{
	run_first();
	return (0);
}
