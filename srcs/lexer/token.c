/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 09:54:12 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:37:39 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/token.h"
#include <stdlib.h>

t_token				*init_token(int type, char *value, t_token *prev)
{
	t_token			*token;

	token = (t_token*)ft_memalloc(sizeof(t_token));
	!token ? exit(1) : 0;
	token->type = type;
	token->value = value;
	token->prev = prev;
	token->next = NULL;
	return (token);
}
