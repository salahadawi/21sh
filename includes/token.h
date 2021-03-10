/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:05:21 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/09 20:21:35 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "./sh.h"

typedef	struct		s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_QSTRING,
		TOKEN_SEMI,
		TOKEN_COMMA,
		TOKEN_PIPE,
		TOKEN_INSERTION,
		TOKEN_EXTRACTION,
		TOKEN_ET,
		TOKEN_ET_SMLER,
		TOKEN_ET_ET,
		TOKEN_ET_LRGER,
		TOKEN_LRGER,
		TOKEN_SMLER,
		TOKEN_SMALER_ET,
		TOKEN_LRGER_ET,
		TOKEN_LRGER_PIPE,
		TOKEN_SM_LR,
		TOKEN_BACKSLASH,
		TOKEN_BACKGROUND,
	}				type;

	int				fd;
	char			*value;
	char			*heredoc;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

t_token				*init_token(int type, char *value, t_token *prev);

#endif
