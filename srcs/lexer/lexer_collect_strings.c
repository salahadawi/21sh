/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:30:06 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/08 15:04:52 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

static char	*lexer_string_qstring(char *new_str)
{
	if (!(new_str = (char*)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	while (new_str && !ft_strchr(new_str, QSTRING))
	{
		ft_printf("\nquote>");
		get_input();
		new_str = ft_relloc(&new_str);
		ft_strcat(new_str, "\n");
		new_str = ft_strjoinfree(new_str, g_21sh->line);
		g_21sh->line = NULL;
	}
	new_str[ft_strlen(new_str) - 1] = '\0';
	return (new_str);
}

static char	*lexer_string_string(char *new_str)
{
	if (!(new_str = (char*)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	while (new_str && !ft_strchr(new_str, STRING))
	{
		ft_printf("\ndquote>");
		get_input();
		new_str = ft_relloc(&new_str);
		ft_strcat(new_str, "\n");
		new_str = ft_strjoinfree(new_str, g_21sh->line);
		g_21sh->line = NULL;
	}
	new_str[ft_strlen(new_str) - 1] = '\0';
	return (new_str);
}

t_token		*lexer_collect_string(t_lexer *lexer)
{
	char	*value;
	char	*s;
	char	*new_str;

	lexer_advance(lexer);
	if (!(value = (char *)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	new_str = NULL;
	while (lexer->c != STRING)
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		if (s[0] == '\0')
		{
			new_str = lexer_string_string(new_str);
			value = ft_strjoinfree(value, new_str);
			free(s);
			break ;
		}
		free(s);
	}
	lexer_advance(lexer);
	return (create_input_token(TOKEN_STRING, value));
}

t_token		*lexer_collect_qstring(t_lexer *lexer)
{
	char	*value;
	char	*s;
	char	*new_str;

	lexer_advance(lexer);
	if (!(value = (char *)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	new_str = NULL;
	while (lexer->c != QSTRING)
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		if (s[0] == '\0')
		{
			new_str = lexer_string_qstring(new_str);
			value = ft_strjoinfree(value, new_str);
			free(s);
			break ;
		}
		free(s);
	}
	lexer_advance(lexer);
	return (create_input_token(TOKEN_QSTRING, value));
}
