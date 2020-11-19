/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:17:40 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/19 14:58:05 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// int			check_stack(int stack[4096], int i, t_token *next)
// {
// 	// ft_printf("\nprev: %d curr: %d next type: %d next: %p\n", prev, curr, next->type, next);
// 	if (i == 0)
// 	if (prev == 99 && curr & OPERATOR)
// 	{
// 		ft_putendl("1");
// 		return (1);
// 	}
// 	else if ((prev & REDIRECTIONS || prev & OPERATOR) && (curr & REDIRECTIONS || curr & OPERATOR))
// 	{
// 		ft_putendl("2");
// 		return (1);
// 	}
// 	else if ((curr & REDIRECTIONS || curr & TOKEN_SMLER) && next == NULL)
// 	{
// 		ft_putendl("3");
// 		return (1);
// 	}
// 	return (0);
// }


int			check_syntax(t_token *token)
{
	t_token		*current;

	current = token;
	while(current)
	{
		if (token->type & OPERATOR)
			return (1);
		else if ((current->prev) && (current->prev->type & REDIRECTIONS || current->type & OPERATOR) && (current->type & REDIRECTIONS || current->type & OPERATOR))
			return (1);
		else if ((current->type & REDIRECTIONS || current->type & TOKEN_SMLER) && current->next == NULL)
			return (1);
		current = current->next;
	}
	return (0);
}