/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_alfa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:39:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:36:34 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "../includes/lexer.h"
#include "../includes/token.h"

t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token		*lexer_collect_backslash(t_lexer *lexer)
{
	char	*value;
	char	*s;
	int		len;
	char	*tmp;

	value = (char*)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	lexer_advance(lexer);
	len = ft_strlen(lexer->contents);
	while (lexer->i < len)
	{
		if (ft_strequ(&lexer->c, " "))
			break ;
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		free(s);
		if (ft_strequ(&lexer->c, "\""))
			break ;
	}
	return (create_input_token(TOKEN_BACKSLASH, value));
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
	while (lexer->c == ' ' || lexer->c == ENTER || lexer->c == TAB)
		lexer_advance(lexer);
}

t_token		*create_input_token(int type, char *value)
{
	t_token *tmp;

	if (!g_21sh->token)
	{
		g_21sh->token = init_token(type, value, NULL);
		return (g_21sh->token);
	}
	else
	{
		tmp = g_21sh->token;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = init_token(type, value, tmp);
		tmp = tmp->next;
		return (tmp);
	}
}
