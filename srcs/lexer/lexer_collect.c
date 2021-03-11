/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:28:37 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/10 09:52:16 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

static char	*lexer_collect(char *value, char *s, t_lexer *lexer)
{
	ft_strcat(value, s);
	value = ft_relloc(&value);
	free(s);
	s = lexer_get_current_char_as_string(lexer);
	ft_strcat(value, s);
	free(s);
	lexer_advance(lexer);
	return (value);
}

t_token		*lexer_collect_lrg(t_lexer *lexer)
{
	char *value;
	char *s;

	s = lexer_get_current_char_as_string(lexer);
	lexer_advance(lexer);
	if (!(value = (char *)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	if (lexer->c == LRG)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_EXTRACTION, value));
	}
	else if (lexer->c == ET)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_LRGER_ET, value));
	}
	else if (lexer->c == PIPE)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_LRGER_PIPE, value));
	}
	ft_strcat(value, s);
	free(s);
	return (create_input_token(TOKEN_LRGER, value));
}

t_token		*lexer_collect_smlr(t_lexer *lexer)
{
	char *value;
	char *s;

	s = lexer_get_current_char_as_string(lexer);
	lexer_advance(lexer);
	if (!(value = (char *)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	if (lexer->c == SML)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_INSERTION, value));
	}
	else if (lexer->c == ET)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_SMALER_ET, value));
	}
	else if (lexer->c == LRG)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_SM_LR, value));
	}
	ft_strcat(value, s);
	free(s);
	return (create_input_token(TOKEN_SMLER, value));
}

t_token		*lexer_collect_et(t_lexer *lexer)
{
	char *value;
	char *s;

	s = lexer_get_current_char_as_string(lexer);
	lexer_advance(lexer);
	if (!(value = (char *)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	if (lexer->c == SML)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_ET_SMLER, value));
	}
	else if (lexer->c == ET)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_ET_ET, value));
	}
	else if (lexer->c == LRG)
	{
		value = lexer_collect(value, s, lexer);
		return (create_input_token(TOKEN_ET_LRGER, value));
	}
	ft_strcat(value, s);
	free(s);
	return (create_input_token(TOKEN_ET, value));
}
