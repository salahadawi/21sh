/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:44:30 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/19 14:58:13 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_ast		*new_leaf(t_token **token)
{
	int		enbr;
	t_ast	*new;
	
	if (!(new = ft_memalloc(sizeof(t_ast))))
		 return (NULL);
	new->token = *token;
	new->token_nbr = 1;
	new->right = NULL;
	new->left = NULL;
	new->parent = NULL;
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

t_ast		*pipe_level(t_token **token)
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

t_ast		*scl_level(t_token **token)
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

t_ast		*create_ast(t_token **token)
{
	t_ast	*root;

	root = scl_level(token);
	return (root);
}

void		print_ast(t_ast *ast)
{

	if (ast != NULL)
	{
		print_ast(ast->right);
		ft_printf("\n%s\n", ast->token->value);
		print_ast(ast->left);
		// print_ast(ast->parent);
		
	}
}
void		run_ast(t_token **token)
{
	t_ast	*ast;

	if ((ast = create_ast(&g_21sh->token)) != NULL)
	{
			init_ast_execution(ast);
			print_ast(ast);
			run_first();
	}
	//delete ast
}

void		parsing_check(t_token **token)
{
	if (!token || !*token)
		return (handle_error("No tokens", 0));
	if (check_syntax(*token) != 0)
		return (handle_error("Syntax error", 0));
	else
	{
		handle_expansion();
		// run_ast(token);
	}
	
	
}