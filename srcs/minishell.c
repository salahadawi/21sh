/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/31 17:57:57 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "../includes/lexer.h"

static void		init_alias(void)
{
	t_alias		*head;

	g_21sh->alias = NULL;
	head = g_21sh->alias;
	g_21sh->head_alias = g_21sh->alias;
}

char			*value_alias(char *value)
{
	t_alias	*current;

	current = g_21sh->alias;
	while (current)
	{
		if ((!ft_strcmp(value, current->alias_name)) &&
		(!ft_strchr(current->real_name, ' ')))
			value = current->real_name;
		current = current->next;
	}
	return (value);
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
		free(g_21sh->line);
	}
}
