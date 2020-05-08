/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/05/08 12:45:45 by sadawi           ###   ########.fr       */
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
# define HOME 72
# define END 70
# define BACKSPACE 127

typedef int				t_builtin_func (char **args);

typedef int				t_shortcut_func (char **args);

typedef struct			s_builtins
{
	char				**names;
	t_builtin_func		**funcs;
	t_shortcut_func		**shortcuts;
}						t_builtins;

typedef	struct			s_key_sequences
{
	char				left_arrow;
	char				right_arrow;
	char				up_arrow;
	char				down_arrow;
	char				delete_key;
}						t_key_sequences;

typedef struct			s_cursor
{
	int					x;
	int					y;
	int					prompt_x;
	int					prompt_y;
}						t_cursor;

typedef struct			s_history
{
	char				*cmd;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct			s_21sh
{
	struct termios		old;
	struct termios		raw;
	t_key_sequences		key_sequences;
	char				**envp;
	t_builtins			builtins;
	t_cursor			cursor;
	int					prompt_len;
	char				*line;
	struct winsize		window;
	char				*history_file_path;
	int					history_fd;
	t_history			*history;
	char				*copied_input;
}						t_21sh;

t_21sh				*g_21sh;

void				print_error(char *message);

int					count_env_amount(char *envp[]);

char				*ft_strsubchar(char const *s, size_t start, char c);

int					builtin_echo(char **args);

int					builtin_exit(char **args);

int					builtin_env(char **args);

int					check_names_match(char *var1, char *var2);

void				add_env(char *arg);

int					builtin_setenv(char **args);

int					shortcut_setenv(char **args);

int					update_env(char **new_envp, int deleted, int i);

int					delete_env(char *arg);

int					builtin_unsetenv(char **args);

char				*strsub_alphanumeric_underscore(char *str);

char				*get_env_value(char *name);

char				*store_oldpwd(void);

void				update_oldpwd(char *path);

void				update_pwd(void);

int					shortcut_cd(char **args);

int					builtin_cd(char **args);

void				init_builtins(void);

void				init_env(char *envp[]);

void				print_envs(void);

char				**split_line_args(char *line);

char				*find_filepath(char *filename);

void				wait_for_child(pid_t pid);

int					exec_cmd(char **args);

int					find_size_pointers(char *str, char *ptr);

int					get_env_name_len(char *str);

char				*expand_tilde(char *str, char *ptr);

char				*expand_dollar(char *str, char *ptr);

char				*find_dollar(const char *s);

void				handle_expansion(char **args);

int					handle_shortcuts(char **args);

int					handle_builtins(char **args);

int					check_cmd(char **args);

int					print_current_dir_basename(void);

void				free_args(char **args);

char				**split_line_commands(char *line);

void				print_shell_info(void);

void				loop_shell(void);

void				clear_screen(void);

char				*create_filepath(char *path, char *filename, int len);

void				init_shortcuts(void);

void				handle_signal(int sig);

void				restore_signals(void);

void				init_signal_handling(void);

void				handle_error(char *message, int reset);

void				set_terminal(char *id);

int					ft_putschar(int c);

void				save_cursor_position(void);

void				restore_terminal_mode(void);

#endif
