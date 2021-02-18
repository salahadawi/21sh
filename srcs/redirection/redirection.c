/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 09:25:16 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/18 09:33:20 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		advance_tokens(void)
{
	t_token *tmp;

	if (!g_21sh->token)
		return (0);
	
	tmp = g_21sh->token->next;
	free_token(g_21sh->token);
	g_21sh->token = tmp;
	return (!!tmp);
}

t_redir		*new_redir(void)
{
	t_redir *redir;

	if (!(redir = (t_redir*)ft_memalloc(sizeof(t_redir))))
		handle_error("Malloc failed", 1);
	redir->type = g_21sh->token->type;
	if (advance_tokens())
	{
		redir->word = ft_strdup(g_21sh->token->value);
		advance_tokens();
	}
	return (redir);
}

t_redir		*new_redir_aggregation(void)
{
	t_redir *redir;

	if (!(redir = (t_redir*)ft_memalloc(sizeof(t_redir))))
		handle_error("Malloc failed", 1);
	if (ft_isdigit(g_21sh->token->value[0]))
		redir->word = ft_itoa(ft_atoi(g_21sh->token->value));
	else
		redir->word = NULL;
	redir->type = g_21sh->token->type;
	if (advance_tokens())
		redir->word2 = ft_strdup(g_21sh->token->value);
	advance_tokens();
	return (redir);
}

int		check_token_redir()
{
	return (g_21sh->token->type == TOKEN_LRGER
	|| g_21sh->token->type == TOKEN_SMLER
	|| g_21sh->token->type == TOKEN_INSERTION
	|| g_21sh->token->type == TOKEN_EXTRACTION);
}

void	add_redir(t_command *command, int aggregation)
{
	static t_redir *cur_redir;

	if (!command->redirections)
	{
		if (aggregation)
			cur_redir = new_redir_aggregation();
		else
			cur_redir = new_redir();
		command->redirections = cur_redir;
	}
	else
	{
		if (aggregation)
			cur_redir->next = new_redir_aggregation();
		else
			cur_redir->next = new_redir();
		cur_redir = cur_redir->next;
	}
}
