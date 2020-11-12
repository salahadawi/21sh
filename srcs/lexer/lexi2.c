/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexi2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:42:33 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/12 07:26:06 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

char		*ft_relloc(char **str)
{
	char	*tmp;

	tmp = ft_strnew(ft_strlen(*str) + 1);
	ft_strcpy(tmp, *str);
	free(*str);
	return (tmp);
}

char		*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char*)malloc(sizeof(char) + 1);
	!str ? exit(1) : 0;
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token		*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = (char*)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	while (ft_isalnum(lexer->c) || (lexer->c == MINUS) || (lexer->c == DOT) ||
	(lexer->c == DOLLAR) || (lexer->c == TILDE) || (lexer->c == SLASH) ||
	(lexer->c == UNDERLINE))
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		free(s);
	}
	return (init_token(TOKEN_ID, value));
}

t_token		*lexer_collect_string(t_lexer *lexer)
{
	char *value;
	char *s;

	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	while (lexer->c != '"')
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		free(s);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_STRING, value));
}

t_token		*lexer_collect_lrg(t_lexer *lexer)
{
	char *value;
	char *s;
	
	s = lexer_get_current_char_as_string(lexer);
	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	if (lexer->c == '>')
	{
		value = ft_relloc(&value);
		ft_strcat(value, s);
		free(s);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		return (init_token(TOKEN_EXTRACTION, value));
	}
	else if (lexer->c == '&')
	{
		value = ft_relloc(&value);
		ft_strcat(value, s);
		free(s);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		return (init_token(TOKEN_LRGER_ET, value));
	}
	else if (lexer->c == '|')
	{
		value = ft_relloc(&value);
		ft_strcat(value, s);
		free(s);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		return (init_token(TOKEN_LRGER_PIPE, value));
	}
	ft_strcat(value, s);
	free(s);
	return (init_token(TOKEN_LRGER, value));
}

t_token		*lexer_collect_smlr(t_lexer *lexer)
{
	char *value;
	char *s;

	s = lexer_get_current_char_as_string(lexer);
	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	if (lexer->c == '<')
	{
		value = ft_relloc(&value);
		ft_strcat(value, s);
		free(s);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		return (init_token(TOKEN_INSERTION, value));
	}
	else if (lexer->c == '&')
	{
		value = ft_relloc(&value);
		ft_strcat(value, s);
		free(s);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		return (init_token(TOKEN_SMALER_ET, value));
	}
	else if (lexer->c == '>')
	{
		value = ft_relloc(&value);
		ft_strcat(value, s);
		free(s);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		return (init_token(TOKEN_SM_LR, value));
	}
	ft_strcat(value, s);
	free(s);
	return (init_token(TOKEN_SMLER, value));
}
