/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:32:28 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/09 20:47:51 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "./token.h"

# define AGGREGATION 1
# define NO_AGGREGATION 0

typedef struct			s_arg
{
	char				*word;
	struct s_arg		*next;
}						t_arg;

typedef struct			s_redir
{
	int					type;
	char				*word;
	char				*word2;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_command
{
	t_arg				*arguments;
	t_redir				*redirections;
	int					num;
	int					background;
	struct s_command	*next;
}						t_command;

typedef struct			s_ast
{
	t_token				*token;
	t_token				*cmd_end;
	struct s_ast		*parent;
	struct s_ast		*left;
	struct s_ast		*right;
	int					type;
	int					token_nbr;
}						t_ast;

void					parsing_check(t_token **token);

#endif
