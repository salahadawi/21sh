/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:59:48 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/24 09:06:17 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_error(char *message)
{
	ft_fprintf(2, "%s\n", message);
	free(message);
}

void	print_shell_info(void)
{
	char	*user;
	int		len;

	len = 0;
	if ((user = get_env_value("USER")))
	{
		len += ft_strlen(user);
		ft_printf(RED "%s" RESET, user);
	}
	len += ft_printf("@");
	len += print_current_dir_basename();
	len += ft_printf("$> ");
	g_21sh->prompt_len = len;
}

int		print_current_dir_basename(void)
{
	char	*path;
	char	*basename;
	int		len;

	if (!(path = (char*)ft_memalloc(PATH_MAX + 1)))
		handle_error("Malloc failed", 1);
	getcwd(path, PATH_MAX);
	basename = ft_strrchr(path, '/') + 1;
	len = ft_strlen(basename);
	ft_printf(BOLDBLUE "%s" RESET, basename);
	free(path);
	return (len);
}
