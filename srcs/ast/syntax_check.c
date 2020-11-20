/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:17:40 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/20 06:43:45 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


int			check_syntax(t_token *token)
{
	t_token		*current;

	current = token;
	while(current)
	{
		if (token->type & OPERATOR)
			return (1);
		else if ((current->prev) && (current->prev->type & REDIRECTIONS ||
		current->type & OPERATOR) && (current->type & REDIRECTIONS || current->type & OPERATOR))
			return (1);
		else if ((current->type & REDIRECTIONS || current->type & TOKEN_SMLER) && current->next == NULL)
			return (1);
		current = current->next;
	}
	return (0);
}