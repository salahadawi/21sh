/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:07:38 by sadawi            #+#    #+#             */
/*   Updated: 2021/04/02 15:36:54 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_exit(char **args)
{
	//restore_terminal_mode(); add later, breaks 'leaks --atExit'
	(void)(args);
	free(g_21sh->line);
	exit(0);
}
