/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:03:41 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 17:51:11 by jochumwilen      ###   ########.fr       */
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
char				*start_lexer_string(char *new_str);
char				*start_lexer_qstring(char *new_str);
char				*lexer_string_qstring(char *new_str);
char				*lexer_string_string(char *new_str);

#endif
