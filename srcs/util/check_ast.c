/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:48:18 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/11 15:18:32 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_ast(void)
{
	t_token *tmp;

	tmp = g_21sh->token;
	while (tmp)
	{
		if (tmp->type == TOKEN_EQUALS && (tmp->prev == NULL))
		{
			print_error(ft_sprintf("\ncommand not found: %s", tmp->value));
			return (1);
		}
		else if (tmp->next == NULL)
		{
			if (tmp->type == TOKEN_INSERTION || tmp->type == TOKEN_EXTRACTION
			|| tmp->type == TOKEN_ET || tmp->type == TOKEN_ET_SMLER || tmp->type
			== TOKEN_LRGER_PIPE || tmp->type == TOKEN_ET_LRGER || tmp->type ==
			TOKEN_SMALER_ET || tmp->type == TOKEN_LRGER_ET || tmp->type ==
			TOKEN_ET_ET || tmp->type == TOKEN_SMLER || tmp->type == TOKEN_SM_LR)
			{
				print_error(ft_sprintf("\nparse error near `%s'", tmp->value));
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
