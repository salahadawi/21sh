/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexi2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:42:33 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/02 14:07:57 by jwilen           ###   ########.fr       */
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

	if (!(str = (char*)malloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int			lexer_collect_file_aggregation(t_lexer *lexer,
char **value, char **s)
{
	int	token_type;

	if (lexer->c &&
		(lexer->c == '<' || lexer->c == '>') &&
		lexer->contents[lexer->i + 1] == '&')
	{
		token_type = lexer->c == '<' ? TOKEN_SMALER_ET : TOKEN_LRGER_ET;
		while (lexer->contents[lexer->i - 1] != '&')
		{
			*value = ft_relloc(value);
			*s = lexer_get_current_char_as_string(lexer);
			ft_strcat(*value, *s);
			lexer_advance(lexer);
			free(*s);
		}
		return (token_type);
	}
	return (0);
}

t_token		*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*s;
	int		token_type;

	if (!(value = (char*)ft_memalloc(sizeof(char) + 1)))
		handle_error("Malloc failed", 1);
	while (lexer->c != '\0' && lexer->c != BACKSLASH && lexer->c != ' ' &&
	lexer->c != ENTER && lexer->c != STRING && lexer->c != QSTRING &&
	lexer->c != ';' && lexer->c != '|' && lexer->c != '>' && lexer->c != '<' &&
	lexer->c != '&')
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		free(s);
	}
	if ((token_type = lexer_collect_file_aggregation(lexer, &value, &s)))
		return (create_input_token(token_type, value));
	return (create_input_token(TOKEN_ID, value));
}
