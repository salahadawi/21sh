/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:30:05 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/06 16:14:52 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_error(char *message, int reset)
{
	ft_fprintf(STDERR_FILENO, "Error: %s.\n", message);
	if (reset)
		restore_terminal_mode();
	//free_memory();
	exit(0);
}
