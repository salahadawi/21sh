/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:56:15 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/18 10:39:26 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_token(t_token *token)
{
	free(token->value);
	free(token->heredoc);
	free(token);
}

int		check_token_fd_aggregation()
{
	return (g_21sh->token->type == TOKEN_SMALER_ET
	|| g_21sh->token->type == TOKEN_LRGER_ET);
}

char	*token_type_to_char(int type) //causes leaks with print_commands, for debug purposes
{
	if (type == TOKEN_LRGER)
		return (ft_strdup(">"));
	if (type == TOKEN_SMLER)
		return (ft_strdup("<"));
	if (type == TOKEN_EXTRACTION)
		return (ft_strdup(">>"));
	if (type == TOKEN_INSERTION)
		return (ft_strdup("<<"));
	return ("ERROR");
}
