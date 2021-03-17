/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:30:05 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/16 08:31:31 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_error(char *message, int reset)
{
	ft_fprintf(STDERR_FILENO, "Error: %s.\n", message);
	if (reset)
		restore_terminal_mode();
	free(g_21sh->line);
}

int		print_invalid_option(char c)
{
	ft_fprintf(STDERR_FILENO, "-%c: invalid option\n", c);
	ft_fprintf(STDERR_FILENO,
		"hash usage [-lr] [-p pathname] [-d] [name ...]\n");
	return (0);
}
