/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:44:30 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/16 05:39:20 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_ast		*new_leaf(t_tok **token)
{
	int		enbr;
	t_ast	*new;
	
	if (!(new = ft_memalloc(sizeof(t_ast))))
		 return (NULL);
	new->token = *token;
	new->token_nbr = 1;
	new->type = (*token)->type;
	enbr = TOKEN_STRING;
	while((*token)->next)
	{
		new->token_nbr++;
		*token = (*token)->next;
	}
	new->cmd_end = !(*token)->next ? (*token)->next : *token;
	return (new);
}

t_ast		*new_node(t_ast *left, t_ast *parent, t_ast *right)
{
	parent->left = left;
	parent->right = right;
	if (left)
		left->parent = parent;
	if (right)
		right->parent = parent;
	return (parent);
}

t_ast		*pipe_level(t_tok **token)
{
	t_ast	*root;
	t_ast	*parent;
	t_ast	*right;

	root = new_leaf(token);
	while ((*token)->type == TOKEN_PIPE)
	{
		parent = new_leaf(token);
		right = new_leaf(token);
		root = new_node(root, parent, right);
	}
	return (root);
}

t_ast		*scl_level(t_tok **token)
{
	t_ast	*root;
	t_ast	*parent;
	t_ast	*right;

	root = pipe_level(token);
	while((*token)->type == TOKEN_SEMI)
	{
		parent = new_leaf(token);
		right = pipe_level(token);
		root = new_node(root, parent, right);
	}
	return (root);
}

t_ast		*create_ast(t_tok **token)
{
	t_ast	*root;

	root = scl_level(token);
	return (root);
}

void		run_ast(t_tok *token)
{
	t_ast	*ast;

	if ((ast = create_ast(&g_21sh->token)) != NULL)
	{
		// run;
	}
	//delete ast
}

void		parsing_check(t_tok **token)
{
	if (!token || !*token)
		return (handle_error("No tokens", 0));
	else
	{
		handle_expansion();
		run_ast(token);
	}
	
	
}