/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 09:54:12 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/12 14:01:42 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/token.h"
#include <stdlib.h>

t_token				*init_token(int type, char *value)
{
	t_token			*token;

	token = (t_token*)malloc(sizeof(t_token));
	!token ? exit(1) : 0;
	token->type = type;
	token->value = value;
	return (token);
}

static t_tok		*create_node_tok(int type, char *str, t_tok *prev)
{
	t_tok	*node;

	if (!(node = (t_tok *)malloc(sizeof(t_tok))))
		exit(1);
	node->str = (char*)str;
	node->type = type;
	node->prev = prev;
	node->next = NULL;
	return (node);
}

void				create_input_tok(int type, char *str)
{
	t_tok *tmp;

	if (!g_21sh->token)
		g_21sh->token = create_node_tok(type, str, NULL);
	else
	{
		tmp = g_21sh->token;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_node_tok(type, str, tmp);
		tmp  = tmp->next;
	}
}
