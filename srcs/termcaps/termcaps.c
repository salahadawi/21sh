/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:00:00 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/08 22:46:46 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#include <errno.h>

void		ft_tcsetpgrp(int fd, pid_t prgp)
{
	//ioctl(fd, TIOCSPGRP, &prgp);

	if (ioctl(fd, TIOCSPGRP, &prgp) == -1)
	{
		ft_fprintf(STDERR_FILENO," MYPID %d. %d, %d: %s\n", getpid(), fd, (int)prgp, strerror(errno));
		//exit(9);
	}
}

pid_t		ft_tcgetpgrp(int fd)
{
	int pgrp;

	if (ioctl (fd, TIOCGPGRP, &pgrp) < 0)
		return (pid_t) -1;
	return (pid_t) pgrp;
}

int		ft_putschar(int c)
{
	if (write(g_21sh->stdout, &c, 1) == -1)
		return (-1);
	return (0);
}

void	init_termcaps(void)
{
	char	*terminal_name;
	pid_t	shell_pgid;

	if (!(isatty(0)))
		handle_error("Not a terminal", 0);
	if (!(terminal_name = getenv("TERM")))
		;//handle_error("Terminal enviroment variable not found", 0);
	if (tgetent(NULL, terminal_name) < 1)
		;//handle_error("Terminal specified in env not found", 0);
	init_key_sequences();
		tcgetattr(STDOUT_FILENO, &g_21sh->old);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &g_21sh->window);

	/* Loop until we are in the foreground.  */
	while (ft_tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
		kill (- shell_pgid, SIGTTIN);
	g_21sh->shell_pgid = getpid();
	if (setpgid (g_21sh->shell_pgid, g_21sh->shell_pgid) < 0)
	{
		ft_fprintf(STDERR_FILENO, "Couldn't put the shell in its own process group");
		exit (1);
    }
	/* Grab control of the terminal.  */
	ft_tcsetpgrp(STDIN_FILENO, g_21sh->shell_pgid); //breaks debugging
}
