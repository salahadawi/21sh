/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:59:48 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:07:16 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *message)
{
	ft_fprintf(2, "%s\n", message);
	free(message);
}

void	print_shell_info(t_env *env)
{
	char *user;

	if ((user = get_env_value(env, "USER")))
		ft_printf(RED "%s" RESET, user);
	ft_printf("@");
	print_current_dir_basename();
	ft_printf("$> ");
}

void	print_current_dir_basename(void)
{
	char *path;

	path = (char*)ft_memalloc(PATH_MAX + 1);
	getcwd(path, PATH_MAX);
	ft_printf(BOLDBLUE "%s" RESET, ft_strrchr(path, '/') + 1);
	free(path);
}
