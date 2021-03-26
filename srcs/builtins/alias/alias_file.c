/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 08:15:30 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/26 20:19:00 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		free_alias(void)
{
	t_alias *tmp;

	if (!g_21sh->alias)
		return ;
	while (g_21sh->alias)
	{
		tmp = g_21sh->alias->next;
		free(g_21sh->alias->real_name);
		free(g_21sh->alias->alias_name);
		free(g_21sh->alias);
		g_21sh->alias = tmp;
	}
}

void		free_alias_node(t_alias **head_ref, t_alias *del)
{
	 /* base case */
    if (*head_ref == NULL || del == NULL)
        return;
 
    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;
 
    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;
 
    /* Change prev only if node to be deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;
 
    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}

char		*produce_back_front(char *line, int i, size_t len, size_t len2)
{
	char	*back;
	char	*front;

	if (i == 1)
	{
		back = (char*)malloc(len2 * sizeof(char));
		ft_memset(back, '\0', sizeof(len2));
		ft_strncpy(back, line + ((len2 + 1) - len), (len));
		return (back);
	}
	else		
	{
		front = (char*)malloc(len2 * sizeof(char));
		ft_memset(front, '\0', sizeof(len2));
		ft_strncpy(front, line, (len2 - len));
		return (front);
	}
	return (NULL);
}

t_alias		*new_alias_node(char *line, t_alias *prev)
{
	t_alias *node;
	size_t	len;
	size_t	len2;
	char	*front;
	char	*back;

	len = ft_strlen(ft_strchr(line, '='));
	len2 = ft_strlen(line);
	if (len2 > 0)
	{
		front = produce_back_front(line, 0, len, len2);
		back = produce_back_front(line, 1, len, len2);
	}
	if (!(node = (t_alias*)ft_memalloc(sizeof(t_alias))))
		handle_error("Malloc failed", 1);
	node->alias_name = ft_strdup(front);
    node->real_name = ft_strdup(back);
	node->prev = prev;
	node->next = NULL;
	return (node);
}

void		add_to_alias(char *line)
{
	t_alias	*current;

	current = g_21sh->alias;
	if (!g_21sh->alias)
		g_21sh->alias = new_alias_node(line, NULL);
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_alias_node(line, current);
		current = current->next;
	}
}

int			alias_file_is_empty(void)
{
	struct stat stats;

	if (stat(g_21sh->alias_file_path, &stats))
		return (1);
	if (stats.st_size <= 1)
		return (1);
	return (0);
}

void		open_alias_file(void)
{
	char *line;

	// g_21sh->alias = NULL;
	g_21sh->alias_fd = open(g_21sh->alias_file_path,
		O_RDWR | O_APPEND | O_CREAT, 0666);
	if (g_21sh->alias_fd == -1)
		return ;
	if (!alias_file_is_empty())
	{
		while (get_next_line(g_21sh->alias_fd, &line) > 0)
		{
			add_to_alias(line);
		}
	}
	add_to_alias(ft_strdup(""));
}

void		get_alias_file_path(void)
{
	char *path;

	if (!(path = (char*)ft_memalloc(PATH_MAX + 1)))
		handle_error("Malloc failed", 1);
	getcwd(path, PATH_MAX);
	path = ft_strjoinfree(path, ft_strdup("/.21sh_alias"));
	g_21sh->alias_file_path = path;
}
