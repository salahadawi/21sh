/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_commands_alfa.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:29:55 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/05 12:12:04 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		filename_character_allowed(char c)
{
	if (!ft_isprint(c))
		return (1);
	if (ft_isalnum(c))
		return (1);
	return (c == '-' || c == '_' || c == '.');
}

void	get_autocomplete_commands(void)
{
	free_autocomp_commands();
	autocomplete_from_path();
	autocomp_commands_append_dir(".");
}
