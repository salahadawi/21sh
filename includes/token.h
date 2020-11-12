/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:05:21 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/12 06:24:02 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef	struct	s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_COMMA,
		TOKEN_PIPE,
		TOKEN_INSERTION,
		TOKEN_EXTRACTION,
		TOKEN_LRGER,
		TOKEN_SMLER,
		TOKEN_SMALER_ET,
		TOKEN_LRGER_ET,
		TOKEN_LRGER_PIPE,
		TOKEN_SM_LR,
		TOKEN_EOF
	}			type;

	char		*value;
}				t_token;

t_token			*init_token(int type, char *value);

#endif
