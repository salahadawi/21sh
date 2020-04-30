/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:28:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/30 13:17:15 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_putschar(int c)
{
	if (write(STDOUT_FILENO, &c, 1) == -1)
		return (-1);
	return (0);
}

void	set_terminal(char *id)
{
	tputs(tgetstr(id, NULL), 1, ft_putschar);
}

void	restore_terminal_mode(void)
{
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->old);
	//set_terminal(CURSOR_VISIBLE);
	//set_terminal(TEXT_NORMAL);
	set_terminal(NORMAL_MODE);
}

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
	g_21sh->key_sequences.delete = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
}

void	init_termcaps(void)
{
	char *terminal_name;

	g_21sh = (t_21sh*)ft_memalloc(sizeof(t_21sh));
	if (!(isatty(0)))
		handle_error("Not a terminal", 0);
	if (!(terminal_name = getenv("TERM")))
		handle_error("Terminal enviroment variable not found", 0);
	if (tgetent(NULL, terminal_name) < 1)
		handle_error("Terminal specified in env not found", 0);
	init_key_sequences();
	tcgetattr(STDOUT_FILENO, &g_21sh->old);
}

void	set_terminal_raw_mode(void)
{
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw);
	set_terminal(SPECIAL_MODE);
}

void	handle_signal_suspend(void)
{
	restore_terminal_mode();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDOUT_FILENO, TIOCSTI, "\032");
}

void	handle_signal_continue(void)
{
	set_terminal_raw_mode();
	signal(SIGTSTP, handle_signal);
}

void	handle_signal_interrupt(void)
{

}

void	handle_signal(int sig)
{
	if (sig == SIGTSTP)
		handle_signal_suspend();
	else if (sig == SIGCONT)
		handle_signal_continue();
	else if (sig == SIGINT)
		handle_signal_interrupt();
	else
	{
		restore_terminal_mode();
		//free_memory(g_select);
		exit(0);
	}
}

void	init_signal_handling(void)
{
	//int i;

	//i = 0;
	//while (i <= SIGRTMAX)
		//signal(i++, handle_signal);
}

void	restore_signals(void)
{
	int i;

	i = 0;
	while (i <= SIGRTMAX)
		signal(i++, SIG_DFL);
}

void	create_terminal_raw_mode()
{
	tcgetattr(STDOUT_FILENO, &g_21sh->raw);
	g_21sh->raw.c_lflag &= ~(ECHO | ICANON);
	g_21sh->raw.c_cc[VMIN] = 0;
	g_21sh->raw.c_cc[VTIME] = 1;
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
