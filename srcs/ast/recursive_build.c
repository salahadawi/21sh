/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 08:43:34 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/02 19:54:18 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

// static int			execute_pipeline(t_ast *left, t_ast *right)
// {
// 	int		fd[2];
// 	int		status;
// 	pid_t	pid_left;

// 	status = 0;
// 	right = left;
// 	left = right;
// 	if (pipe(fd) == -1)
// 	{
// 		print_error("pipe error");
// 		return (1);
// 	}
// 	else if ((pid_left = fork()) == -1)
// 		exit(1);
// 	else if (!pid_left)
// 	{
// 		close(fd[0]);
// 		// dup21(fd[1], STDOUT_FILENO, left->token->value);
// 		exit(1);
// 	}
// 	else
// 	{
// 		close(fd[0]);
// 		waitpid(pid_left, NULL, 0);
// 	}
// 	return (status);
// }

// static int			recurse_pipe(t_ast *ast)
// {
// 	if (!ast->left)
// 		return (execute_pipeline(ast, ast->parent->right));
// 	else
// 		return (recurse_pipe(ast->left));
// }

// static int			recurse_semi(t_ast *ast)
// {
// 	init_ast_execution(ast->left);
// 	return (init_ast_execution(ast->right));
// }

// int					init_ast_execution(t_ast *ast)
// {
// 	if (ast->token->type == TOKEN_SEMI)
// 		return (recurse_semi(ast));
// 	else if (ast->token->type == TOKEN_PIPE)
// 		return (recurse_pipe(ast));
// 	else
// 		return (0);
// }
