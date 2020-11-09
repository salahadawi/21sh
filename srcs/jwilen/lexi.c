/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 07:22:21 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/09 18:07:36 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

t_lexer		*init_lexer(char *contents)
{
	t_lexer		*lexer;

	lexer = (t_lexer*)malloc(sizeof(t_lexer));
	!lexer ? exit(1) : 0;
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void		lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void		lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
		lexer_advance(lexer);
}

t_token		*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ' || lexer->c == ENTER)
			lexer_skip_whitespace(lexer);
		if (ft_isalnum(lexer->c) || (lexer->c == TILDE) || (lexer->c == DOT) ||
		(lexer->c == MINUS) || (lexer->c == DOLLAR) || (lexer->c == SLASH) ||
		(lexer->c == UNDERLINE))
			return (lexer_collect_id(lexer));
		if (lexer->c == '"')
			return (lexer_collect_string(lexer));
		if (lexer->c == ';')
			return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMI,
			lexer_get_current_char_as_string(lexer))));
			break ;
	}
	return (init_token(TOKEN_EOF, "\0"));
}

void		lexi()
{
	t_lexer *lexer;
	t_token *token;

	token = NULL;
	lexer = init_lexer(g_21sh->line);
	g_21sh->token = NULL;
	while ((token = lexer_get_next_token(lexer)))
	{
		if (token->type == TOKEN_EOF)
		{
			free(token);
			break ;
		}
		create_input_tok(token->value);
		free(token);
	}
	free(lexer);
}
