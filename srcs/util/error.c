/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:30:05 by jwilen            #+#    #+#             */
/*   Updated: 2021/04/02 14:55:29 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_error(char *message, int reset)
{
	ft_fprintf(STDERR_FILENO, "Error: %s.\n", message);
	if (reset)
		restore_terminal_mode();
	free(g_21sh->line);
	exit(1);
}

int		print_invalid_option(char c)
{
	ft_fprintf(STDERR_FILENO, "-%c: invalid option\n", c);
	ft_fprintf(STDERR_FILENO,
		"hash usage [-lr] [-p pathname] [-d] [name ...]\n");
	return (0);
}
