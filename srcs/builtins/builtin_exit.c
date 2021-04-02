/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:07:38 by sadawi            #+#    #+#             */
/*   Updated: 2021/04/03 00:04:59 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_exit(char **args)
{
	restore_terminal_mode();
	(void)(args);
	free(g_21sh->line);
	exit(0);
}
