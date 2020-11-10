/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:14:50 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/10 11:29:57 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**split_line_args(char *line)
{
	char **args;
	while(g_21sh->token)
	{
		args = &g_21sh->token->str;
		g_21sh->token = g_21sh->token->next;
	}
	// args = ft_strsplitws(line);
	return (args);
}

char	**split_line_commands(char *line)
{
	char **args;

	while(g_21sh->token)
	{
		args = &g_21sh->token->str;
		g_21sh->token = g_21sh->token->next;
	}
	// args = ft_strsplit(line, ';');
	return (args);
}
