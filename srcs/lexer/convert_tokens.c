/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:20:57 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/22 12:29:31 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

// are theese functions used at all ?
void		ft_free_s_data(void)
{
	int		i;

	i = 0;
	while (g_21sh->s_args[i])
	{
		ft_strdel(&g_21sh->s_args[i]);
		i++;
	}
	free(g_21sh->s_args);
}

int			list_len_token(void)
{
	t_token		*current;
	int			len;

	len = 0;
	current = g_21sh->head;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

int			array_len_arr(int i)
{
	int		len;

	len = 0;
	while (g_21sh->args[i] != NULL && !ft_strequ(g_21sh->args[i], ";"))
	{
		len++;
		i++;
	}
	return (len);
}

void		convert_arr_tok_to_arr(void)
{
	int		len;
	int		i;
	int		j;

	i = 0;
	while (g_21sh->args[i])
	{
		j = 0;
		len = array_len_arr(i);
		g_21sh->s_args = (char **)ft_memalloc(sizeof(char*) * (len + 1));
		while (len > 0)
		{
			g_21sh->s_args[j] = ft_strdup(g_21sh->args[i]);
			j++;
			i++;
			len--;
		}
		g_21sh->s_args[j] = NULL;
		ft_printf("\n");
		if (handle_builtins(g_21sh->s_args))
			write(1, "", 0);
		else
			exec_cmd(g_21sh->s_args);
		ft_free_s_data();
		if (g_21sh->args[i] != NULL)
			i++;
		if (g_21sh->args[i] == NULL)
			break ;
	}
}

void		convert_ll_to_arr_tok(void)
{
	int		len;
	t_token	*current;
	int		i;

	len = list_len_token();
	i = 0;
	g_21sh->args = malloc(sizeof(char *) * (len + 1));
	if (!g_21sh->args)
	{
		ft_printf("Malloc failed\n");
		exit(1);
	}
	current = g_21sh->token;
	while (current)
	{
		g_21sh->args[i] = current->value;
		current = current->next;
		i++;
	}
	g_21sh->args[i] = NULL;
}

void		run_first(void)
{
	convert_ll_to_arr_tok();
	convert_arr_tok_to_arr();
}
