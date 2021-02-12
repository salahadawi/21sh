/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_commands_alfa.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:29:55 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/12 09:38:53 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_autocomplete_commands(void)
{
	free_autocomp_commands();
	autocomplete_from_path();
	autocomp_commands_append_dir(".");
	//print_autocomp_commands();
}