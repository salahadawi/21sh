/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:03:41 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:34:27 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./token.h"

typedef struct		s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
}					t_lexer;

char				*ft_relloc(char **str);
t_lexer				*init_lexer(char *contents);
void				lexer_advance(t_lexer *lexer);
void				lexer_skip_whitespace(t_lexer *lexer);
t_token				*lexer_get_next_token(t_lexer *lexer);
t_token				*lexer_collect_string(t_lexer *lexer);
t_token				*lexer_collect_qstring(t_lexer *lexer);
t_token				*lexer_collect_backslash(t_lexer *lexer);
t_token				*lexer_collect_lrg(t_lexer *lexer);
t_token				*lexer_collect_smlr(t_lexer *lexer);
t_token				*lexer_collect_id(t_lexer *lexer);
t_token				*lexer_collect_et(t_lexer *lexer);
t_token				*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char				*lexer_get_current_char_as_string(t_lexer *lexer);

#endif
