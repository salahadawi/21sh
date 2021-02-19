/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:17:40 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/19 10:13:43 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_syntax(t_token *token)
{
	t_token		*current;

	current = token;
	while (current)
	{
		ft_printf("\ntoken type: %d\n", token->type);
		if (token->type & OPERATOR)
		{
			write(1, "1", 1);
			return (1);
		}
		else if ((current->prev) && (current->prev->type & REDIRECTIONS ||
		current->type & OPERATOR) && (current->type & REDIRECTIONS || current->type & OPERATOR))
		{
			write(1, "2", 1);
			return (1);
		}
		else if ((current->type & REDIRECTIONS || current->type & TOKEN_SMLER) && current->next == NULL)
		{
			write(1, "3", 1);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
