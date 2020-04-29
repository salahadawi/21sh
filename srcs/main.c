/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:28:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:23:16 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_putschar(int c)
{
	if (write(STDERR_FILENO, &c, 1) == -1)
		return (-1);
	return (0);
}

void	set_terminal(char *id)
{
	tputs(tgetstr(id, NULL), 1, ft_putschar);
}

void	restore_terminal_mode(void)
{
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &g_21sh->old);
	//set_terminal(CURSOR_VISIBLE);
	//set_terminal(TEXT_NORMAL);
	set_terminal(NORMAL_MODE);
}

void	handle_error(char *message, int reset)
{
	ft_fprintf(STDERR_FILENO, "Error: %s.\n", message);
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
	g_21sh->key_sequences.delete = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
}

void	init_termcaps(void)
{
	char *terminal_name;

	g_21sh = (t_21sh*)ft_memalloc(sizeof(g_21sh));
	if (!(isatty(0)))
		handle_error("Not a terminal", 0);
	if (!(terminal_name = getenv("TERM")))
		handle_error("Terminal enviroment variable not found", 0);
	if (tgetent(NULL, terminal_name) < 1)
		handle_error("Terminal specified in env not found", 0);
	init_key_sequences();
}

int		main(int argc, char **argv, char *envp[])
{
	init_termcaps();
	(void)(argc && argv);
	init_env(envp);
	clear_screen();
	loop_shell();
	return (0);
}
