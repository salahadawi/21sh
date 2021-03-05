/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:40:24 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/05 12:52:06 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_arg		*new_arg(void)
{
	t_arg *arg;

	if (!(arg = (t_arg*)ft_memalloc(sizeof(t_arg))))
		handle_error("Malloc failed", 1);
	arg->word = ft_strdup(g_21sh->token->value);
	advance_tokens();
	return (arg);
}

void		add_arg(t_command *command)
{
	static t_arg *cur_arg;

	if (!command->arguments)
	{
		cur_arg = new_arg();
		command->arguments = cur_arg;
	}
	else
	{
		cur_arg->next = new_arg();
		cur_arg = cur_arg->next;
	}
}
