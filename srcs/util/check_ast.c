/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:48:18 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/09 11:43:40 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	free_error_token(t_token *lst)
{
	t_token *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		// free(tmp->value);
		// free(tmp);
	}
}

void		check_ast()
{
	t_token *tmp;

	tmp = g_21sh->token;
	while (tmp)
	{
		print_error(ft_sprintf("%d ", tmp->type));
		if (tmp->type == TOKEN_EQUALS && (tmp->next == NULL || tmp->prev == NULL))
		{
			print_error(ft_sprintf("command not found: %s", tmp->value));
			free_error_token(g_21sh->token);
		}
		else if (tmp->next == NULL)
		{
			if (tmp->type == TOKEN_INSERTION || tmp->type == TOKEN_EXTRACTION ||
			tmp->type == TOKEN_ET || tmp->type == TOKEN_ET_SMLER || tmp->type == TOKEN_ET_ET || 
			tmp->type == TOKEN_ET_LRGER || tmp->type == TOKEN_SMLER || tmp->type == TOKEN_SMALER_ET ||
			tmp->type == TOKEN_LRGER_ET || tmp->type == TOKEN_LRGER_PIPE || tmp->type == TOKEN_SM_LR)
			{
				print_error(ft_sprintf("parse error near `%s'", tmp->value));
				free_error_token(g_21sh->token);
			}
		}
		tmp = tmp->next;
	}
}