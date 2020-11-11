/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:30:05 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/11 17:30:18 by jwilen           ###   ########.fr       */
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
