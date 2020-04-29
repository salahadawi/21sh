/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:14:50 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 12:49:41 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**split_line_args(char *line)
{
	char **args;

	args = ft_strsplitws(line);
	return (args);
}

char	**split_line_commands(char *line)
{
	char **args;

	args = ft_strsplit(line, ';');
	return (args);
}
