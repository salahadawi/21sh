/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_start_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:49:55 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/03/31 17:50:04 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

char		*start_lexer_string(char *new_str)
{
	if (g_21sh->line)
		free(g_21sh->line);
	new_str = lexer_string_string(new_str);
	return (new_str);
}

char		*start_lexer_qstring(char *new_str)
{
	if (g_21sh->line)
		free(g_21sh->line);
	new_str = lexer_string_qstring(new_str);
	return (new_str);
}
