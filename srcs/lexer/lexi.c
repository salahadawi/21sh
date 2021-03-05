/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 07:22:21 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/05 12:35:36 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

static t_token	*lexer_what(t_lexer *lexer)
{
	if (lexer->c == STRING)
		return (lexer_collect_string(lexer));
	if (lexer->c == QSTRING)
		return (lexer_collect_qstring(lexer));
	if (lexer->c == LRG)
		return (lexer_collect_lrg(lexer));
	if (lexer->c == SML)
		return (lexer_collect_smlr(lexer));
	if (lexer->c == ET)
		return (lexer_collect_et(lexer));
	else if (lexer->c)
		return (lexer_collect_id(lexer));
	return (0);
}

t_token			*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == BACKSLASH)
			return (lexer_collect_backslash(lexer));
		if (lexer->c == ' ' || lexer->c == ENTER || lexer->c == TAB)
			lexer_skip_whitespace(lexer);
		if (lexer->c == ';')
		{
			return (lexer_advance_with_token(lexer,
			create_input_token(TOKEN_SEMI,
			lexer_get_current_char_as_string(lexer))));
			break ;
		}
		if (lexer->c == PIPE)
		{
			return (lexer_advance_with_token(lexer,
			create_input_token(TOKEN_PIPE,
			lexer_get_current_char_as_string(lexer))));
			break ;
		}
		lexer_what(lexer);
	}
	return (NULL);
}

t_lexer			*init_lexer(char *contents)
{
	t_lexer		*lexer;

	if (!(lexer = (t_lexer*)malloc(sizeof(t_lexer))))
		handle_error("Malloc failed", 1);
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void			lexi(void)
{
	t_lexer *lexer;
	t_token *token;

	lexer = init_lexer(g_21sh->line);
	g_21sh->token = NULL;
	g_21sh->head = g_21sh->token;
	while ((token = lexer_get_next_token(lexer)))
		token = token->next;
	free(lexer);
}
