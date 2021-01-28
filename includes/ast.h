/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:32:28 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/16 10:46:36 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "./token.h"

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
