/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 12:48:45 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "../libft/includes/libft.h"
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <dirent.h>
# include <linux/limits.h>
# include <signal.h>
# include <fcntl.h>

# define BOLDBLUE "\033[1m\033[36m"
# define RED "\033[1m\033[31m"
# define RESET "\033[0m"

# define CLEAR_SCREEN "cl"
# define LEFT_SEQUENCE "kl"
# define RIGHT_SEQUENCE "kr"
# define UP_SEQUENCE "ku"
# define DOWN_SEQUENCE "kd"
# define DELETE_SEQUENCE "kD"
# define SPECIAL_MODE "ti"
# define NORMAL_MODE "te"

# define DELETE -49
# define ENTER 10
# define ESCAPE 27
# define SPACE 32
# define BACKSPACE 127

struct s_env;

typedef int			t_builtin_func (struct s_env *env, char **args);

typedef int			t_shortcut_func (struct s_env *env, char **args);

typedef struct		s_env
{
	char			**envp;
	char			**builtin_names;
	t_builtin_func	**builtin_funcs;
	t_shortcut_func	**shortcut_funcs;
}					t_env;

typedef	struct		s_key_sequences
{
	char			left_arrow;
	char			right_arrow;
	char			up_arrow;
	char			down_arrow;
	char			delete;
}					t_key_sequences;

typedef struct		s_21sh
{
	struct termios	old;
	struct termios	raw;
	t_key_sequences	key_sequences;
}					t_select;

void				print_error(char *message);

int					count_env_amount(char *envp[]);

char				*ft_strsubchar(char const *s, size_t start, char c);

int					builtin_echo(t_env *env, char **args);

int					builtin_exit(t_env *env, char **args);

int					builtin_env(t_env *env, char **args);

int					check_names_match(char *var1, char *var2);

void				add_env(t_env *env, char *arg);

int					builtin_setenv(t_env *env, char **args);

int					shortcut_setenv(t_env *env, char **args);

int					update_env(t_env *env, char **new_envp, int deleted, int i);

int					delete_env(t_env *env, char *arg);

int					builtin_unsetenv(t_env *env, char **args);

char				*strsub_alphanumeric_underscore(char *str);

char				*get_env_value(t_env *env, char *name);

char				*store_oldpwd(void);

void				update_oldpwd(t_env *env, char *path);

void				update_pwd(t_env *env);

int					shortcut_cd(t_env *env, char **args);

int					builtin_cd(t_env *env, char **args);

void				init_builtins(t_env *env);

void				init_env(t_env **env, char *envp[]);

void				print_envs(t_env *env);

char				**split_line_args(char *line);

char				*find_filepath(t_env *env, char *filename);

void				wait_for_child(pid_t pid);

int					exec_cmd(t_env *env, char **args);

int					find_size_pointers(char *str, char *ptr);

int					get_env_name_len(char *str);

char				*expand_tilde(t_env *env, char *str, char *ptr);

char				*expand_dollar(t_env *env, char *str, char *ptr);

char				*find_dollar(const char *s);

void				handle_expansion(t_env *env, char **args);

int					handle_shortcuts(t_env *env, char **args);

int					handle_builtins(t_env *env, char **args);

int					check_cmd(t_env *env, char **args);

void				print_current_dir_basename(void);

void				free_args(char **args);

char				**split_line_commands(char *line);

void				print_shell_info(t_env *env);

void				loop_shell(t_env *env);

void				clear_screen(t_env *env);

char				*create_filepath(char *path, char *filename, int len);

void				init_shortcuts(t_env *env);

#endif
