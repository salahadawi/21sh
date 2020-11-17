/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:28:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/10/23 14:43:38 by sadawi           ###   ########.fr       */
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
	g_21sh->key_sequences.delete_key = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
}

void	init_termcaps(void)
{
	char *terminal_name;

	g_21sh = (t_21sh*)ft_memalloc(sizeof(t_21sh));
	//set all variables to NULL in function?
	g_21sh->copied_input = NULL;
	if (!(isatty(0)))
		handle_error("Not a terminal", 0);
	if (!(terminal_name = getenv("TERM")))
		handle_error("Terminal enviroment variable not found", 0);
	if (tgetent(NULL, terminal_name) < 1)
		handle_error("Terminal specified in env not found", 0);
	init_key_sequences();
	tcgetattr(STDOUT_FILENO, &g_21sh->old);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_21sh->window);
}

void	set_terminal_raw_mode(void)
{
	g_21sh->raw.c_lflag &= ~(ECHO | ICANON);
	g_21sh->raw.c_cc[VMIN] = 0;
	g_21sh->raw.c_cc[VTIME] = 1;
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
	free(g_21sh->line);
	g_21sh->line = ft_strnew(1);
	ft_printf("\n");
	print_shell_info();
	g_21sh->cursor.x = 0;
	save_cursor_position();
}

void	handle_signal_resize(void)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_21sh->window);
	if ((int)ft_strlen(g_21sh->line) >= g_21sh->window.ws_col * g_21sh->window.ws_row)
	{
		set_terminal("ho");
		set_terminal("cr");
		print_shell_info();
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGTSTP)
		handle_signal_suspend();
	else if (sig == SIGCONT)
		handle_signal_continue();
	else if (sig == SIGINT)
		handle_signal_interrupt();
	else if (sig == SIGWINCH)
		handle_signal_resize();
	else
	{
		restore_terminal_mode();
		//free_memory(g_select);
		exit(0);
	}
}

void	init_signal_handling(void)
{
	int i;

	i = 0;
	while (i <= 30)
		signal(i++, handle_signal);
}

void	restore_signals(void)
{
	int i;

	i = 0;
	while (i <= 30)
		signal(i++, SIG_DFL);
}

void	create_terminal_raw_mode()
{
	tcgetattr(STDOUT_FILENO, &g_21sh->raw);
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
