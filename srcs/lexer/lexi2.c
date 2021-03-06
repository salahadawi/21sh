/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexi2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:42:33 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/10 17:25:51 by sadawi           ###   ########.fr       */
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

static int	ft_check_c(int c)
{
	return ((60 < c && c < 123) || ('0' <= c && c <= '9'));
}

int			lexer_collect_file_aggregation(t_lexer *lexer, char **value, char **s)
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

	value = (char*)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
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

t_token		*lexer_collect_string(t_lexer *lexer)
{
	char *value;
	char *s;
	char *new_str;

	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	while (lexer->c != STRING)
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		if (s[0] == '\0')
        {
			new_str = (char*)ft_memalloc(sizeof(char));
            while (new_str && !ft_strchr(new_str, STRING))
            {
                ft_printf("\ndquote>");
                get_input();
				new_str = ft_relloc(&new_str);
			    ft_strcat(new_str, "\n");
				new_str = ft_strjoinfree(new_str, g_21sh->line);
				g_21sh->line = NULL;
            }
			new_str[ft_strlen(new_str) -1] = '\0';
            value = ft_strjoinfree(value, new_str);
            break;
        }
		free(s);
	}
	lexer_advance(lexer);
	return (create_input_token(TOKEN_STRING, value));
}

t_token		*lexer_collect_qstring(t_lexer *lexer)
{
	char *value;
	char *s;
	char	*new_str;

	lexer_advance(lexer);
	value = (char *)ft_memalloc(sizeof(char));
	!value ? exit(1) : 0;
	while (lexer->c != QSTRING)
	{
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		if (s[0] == '\0')
        {
			new_str = (char*)ft_memalloc(sizeof(char));
            while (new_str && !ft_strchr(new_str, QSTRING))
            {
                ft_printf("\nquote>");
                get_input();
				new_str = ft_relloc(&new_str);
			    ft_strcat(new_str, "\n");
				new_str = ft_strjoinfree(new_str, g_21sh->line);
				g_21sh->line = NULL;
            }
            new_str[ft_strlen(new_str) -1] = '\0';
            value = ft_strjoinfree(value, new_str);
            break;
        }
		free(s);
	}
	lexer_advance(lexer);
	return (create_input_token(TOKEN_QSTRING, value));
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
			break;
		value = ft_relloc(&value);
		s = lexer_get_current_char_as_string(lexer);
		ft_strcat(value, s);
		lexer_advance(lexer);
		free(s);
		if (ft_strequ(&lexer->c, "\""))
			break;
	}
	return (create_input_token(TOKEN_BACKSLASH,value));
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
		return (create_input_token(TOKEN_EXTRACTION, value));
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
		return (create_input_token(TOKEN_LRGER_ET, value));
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
		return (create_input_token(TOKEN_INSERTION, value));
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
		return (create_input_token(TOKEN_SMALER_ET, value));
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
		return (create_input_token(TOKEN_ET_SMLER, value));
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
		return (create_input_token(TOKEN_ET_ET, value));
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
		return (create_input_token(TOKEN_ET_LRGER, value));
	}
	ft_strcat(value, s);
	free(s);
	return (create_input_token(TOKEN_ET, value));
}