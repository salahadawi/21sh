/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:30:05 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/25 20:34:38 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_error(char *message, int reset)
{
	ft_fprintf(STDERR_FILENO, "Error: %s.\n", message);
	if (reset)
		restore_terminal_mode();
	free(g_21sh->line);
	//exit(0);
}
