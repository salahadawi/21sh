/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:28:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/11 17:03:21 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_error(char *message, int reset)
{
	ft_fprintf(STDOUT_FILENO, "Error: %s.\n", message);
	if (reset)
		restore_terminal_mode();
	//free_memory();
	exit(0);
}

void	init_key_sequences()
{
	char *sequence;

	sequence = tgetstr(LEFT_SEQUENCE, NULL);
	g_21sh->key_sequences.left_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(RIGHT_SEQUENCE, NULL);
	g_21sh->key_sequences.right_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(UP_SEQUENCE, NULL);
	g_21sh->key_sequences.up_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(DOWN_SEQUENCE, NULL);
	g_21sh->key_sequences.down_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(DELETE_SEQUENCE, NULL);
	g_21sh->key_sequences.delete_key = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
}

int		main(int argc, char **argv, char *envp[])
{
	(void)(argc && argv);
	init_termcaps();
	init_signal_handling();
	create_terminal_raw_mode();
	set_terminal_raw_mode();
	init_env(envp);
	clear_screen();
	loop_shell();
	restore_terminal_mode();
	return (0);
}
