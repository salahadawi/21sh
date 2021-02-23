/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:30:06 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:31:15 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

static char	*lexer_string_1(char *new_str, char chr)
{
	new_str = (char*)ft_memalloc(sizeof(char));
	!new_str ? exit(1) : 0;
	while (new_str && !ft_strchr(new_str, chr))
	{
		chr == STRING ? ft_printf("\ndquote>") : ft_printf("\nquote>");
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
	char	chr;

	chr = lexer->c;
	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	while (lexer->c != chr)
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		if (s[0] == '\0')
		{
			new_str = lexer_string_1(new_str, chr);
			value = ft_strjoinfree(value, new_str);
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
	char	chr;

	chr = lexer->c;
	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	while (lexer->c != chr)
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		if (s[0] == '\0')
		{
			new_str = lexer_string_1(new_str, chr);
			value = ft_strjoinfree(value, new_str);
			break ;
		}
		free(s);
	}
	lexer_advance(lexer);
	return (create_input_token(TOKEN_QSTRING, value));
}
