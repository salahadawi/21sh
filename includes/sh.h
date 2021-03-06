/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/10 18:14:09 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "../libft/includes/libft.h"
# include "./token.h"
# include "./ast.h"

# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>

# define BOLDBLUE "\033[1m\033[36m"
# define RED "\033[1m\033[31m"
# define RESET "\033[0m"

# ifndef linux
# define SIGRTMAX 64
# endif

# define FILENAME_MAX_SIZE 255

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
# define TAB 9
// jwi
# define STRING 34
# define DOLLAR 36
# define QSTRING 39
# define MINUS 45
# define SLASH 47
# define EQUAL 61
# define BACKSLASH 92
# define DOT 46
# define UNDERLINE 95
# define PIPE 124
# define TILDE 126

# define TEXT_INVERSE_VIDEO "mr"
# define TEXT_UNDERLINE "us"
# define TEXT_NORMAL "me"

// # define OPERATOR (TOKEN_SEMI | TOKEN_PIPE | TOKEN_LRGER | TOKEN_SMLER | TOKEN_ET)

# define OPERATOR (TOKEN_SEMI | TOKEN_PIPE | TOKEN_LRGER | TOKEN_SMLER | TOKEN_ET)
# define REDIRECTIONS (TOKEN_SMLER | TOKEN_LRGER | TOKEN_INSERTION | TOKEN_EXTRACTION)

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

typedef struct		s_tok
{
	char			*str;
	int				type;
	struct s_tok	*prev;
	struct s_tok	*next;
}					t_tok;

typedef struct			s_autocomp
{
	char				command[FILENAME_MAX_SIZE * 2 + 1]; // Times 2 in case each character needs to be escaped
	struct s_autocomp	*next;
}						t_autocomp;

typedef struct			s_21sh
{
	struct termios		old;
	struct termios		raw;
	t_key_sequences		key_sequences;
	char				**envp;
	char				**args;
	char				**s_args;
	t_builtins			builtins;
	t_cursor			cursor;
	int					prompt_len;
	char				*line;
	char				*read_more;
	struct winsize		window;
	char				*history_file_path;
	int					history_fd;
	t_history			*history;
	char				*copied_input;
	t_token				*head;
	t_token				*token;
	t_autocomp			*autocomp;
	t_autocomp			*autocomp_tail;
	char				previous_pressed_key;
	t_cursor			cursor_heredoc;
	int					stdin;
	int					stdout;
	char				*copy_part;
	int					copy_start;
	int					copy_end;
}						t_21sh;

t_21sh				*g_21sh;
int					g_debug;

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

void				handle_expansion(void);

int					handle_shortcuts(char **args);

int					handle_builtins(char **args);

int					check_cmd(void);

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

void				lexi(void);

void				create_input_tok(int type, char *str);
t_token				*create_input_token(int type, char *value);
int					list_len_token();

void				run_first(void);

void				move_cursor_right_edge(void);
void				move_cursor_next_line(void);
void				move_cursor_start(void);
void				move_cursor_up(void);
void				move_cursor_down(void);
void				move_cursor_left(void);
void				move_cursor_right(void);
void				move_word_right(void);
void				move_word_left(void);
void				move_cursor(void);
void				cursor_jump_up(int *left_len);

int					handle_keys(void);
int					read_key(void);
char				*str_remove_char(char *str, int index);
char				*str_add_char(char *str, char c);
void				handle_delete(void);

void				get_history_file_path(void);
void				get_history_prev(void);
void				get_history_next(void);
void				open_history_file(void);
void				add_to_history(char *line);
void				save_command_history(void);
int					same_as_previous_command();
void				free_history(void);

void				init_termcaps(void);

void				create_terminal_raw_mode();
void				set_terminal_raw_mode(void);

void				handle_signal_suspend(void);
void				handle_signal_continue(void);
void				handle_signal_interrupt(void);
void				handle_signal_resize(void);

int					get_input();
void				check_str(void);
int					brackets(char *str);

void				find_prompt_y(void);
void				init_key_sequences();
char				*str_add_str(char *str, char *str2);

int					init_ast_execution(t_ast *ast);

int			check_syntax(t_token *token);

void	print_input();
int		input_too_large(void);

int		filename_character_allowed(char c);

void	autocomplete(char **line, char previous_pressed_key);

void        copy_start();
void            paste();
char	*str_add_paste(char *str, char *paste);


#endif
