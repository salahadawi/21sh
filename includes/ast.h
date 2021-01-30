/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:32:28 by jwilen            #+#    #+#             */
/*   Updated: 2021/01/30 16:36:11 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "./token.h"

typedef struct			s_args
{
	char				*word;
	struct s_args		*next;
}						t_args;

typedef struct			s_redirs
{
	int					type;
	char				*word;
	struct s_redirs		*next;
}						t_redirs;

typedef struct			s_command
{
	t_args				*arguments;
	t_redirs			*redirections;
	struct s_command	*next;
}						t_command;

typedef struct 		s_ast
{
	t_token			*token;
	t_token			*cmd_end;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	int				type;
	int				token_nbr;
}					t_ast;

void		parsing_check(t_token **token);

#endif
