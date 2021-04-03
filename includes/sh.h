/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:20:24 by sadawi            #+#    #+#             */
/*   Updated: 2021/04/03 13:10:45 by sadawi           ###   ########.fr       */
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
#  define SIGRTMAX 64
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
# define CTRL_D 4
# define ENTER 10
# define CTRL_K 11
# define CTRL_P 16
# define CTRL_U 21
# define ESCAPE 27
# define HOME 72
# define END 70
# define BACKSPACE 127
# define TAB 9
# define STRING 34
# define DOLLAR 36
# define ET 38
# define QSTRING 39
# define MINUS 45
# define SLASH 47
# define SML 60
# define EQUAL 61
# define LRG 62
# define BACKSLASH 92
# define DOT 46
# define UNDERLINE 95
# define PIPE 124
# define TILDE 126

# define TEXT_INVERSE_VIDEO "mr"
# define TEXT_UNDERLINE "us"
# define TEXT_NORMAL "me"

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

typedef struct			s_alias
{
	char				*alias_name;
	char				*real_name;
	struct s_alias		*prev;
	struct s_alias		*next;
}						t_alias;

typedef struct			s_tok
{
	char				*str;
	int					type;
	struct s_tok		*prev;
	struct s_tok		*next;
}						t_tok;

typedef struct			s_autocomp
{
	char				command[FILENAME_MAX_SIZE * 2 + 1];
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
	t_alias				*alias;
	t_alias				*head_alias;
	int					alias_fd;
	char				*alias_file_path;
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
	struct s_hashmap	*hashmap;
}						t_21sh;

t_21sh					*g_21sh;
int						g_debug;

void					free_command(t_command *commands);
void					free_arg(t_arg *arg);
void					print_error(char *message);
/*
** built in functions
*/
int						count_env_amount(char *envp[]);
char					*ft_strsubchar(char const *s, size_t start, char c);
int						builtin_echo(char **args);
int						builtin_exit(char **args);
int						builtin_env(char **args);
int						builtin_hash(char **args);
int						builtin_type(char **args);
int						builtin_test(char **args);
int						builtin_alias(char **args);
int						builtin_unalias(char **args);
int						check_names_match(char *var1, char *var2);
void					add_env(char *arg);
int						builtin_setenv(char **args);
int						shortcut_setenv(char **args);
int						update_env(char **new_envp, int deleted, int i);
int						delete_env(char *arg);
int						builtin_unsetenv(char **args);
char					*strsub_alphanumeric_underscore(char *str);
char					*get_env_value(char *name);
char					*store_oldpwd(void);
void					update_oldpwd(char *path);
void					update_pwd(void);
int						shortcut_cd(char **args);
int						builtin_cd(char **args);
void					init_builtins(void);
void					init_env(char *envp[]);
void					print_envs(void);
int						handle_builtins(char **args);
char					**split_line_args(char *line);
char					*find_filepath(char *filename);
void					wait_for_child(pid_t pid);
int						exec_cmd(char **args);
int						find_size_pointers(char *str, char *ptr);
int						get_env_name_len(char *str);

/*
** Expand tilde & dollar functions
*/
char					*expand_tilde(char *str, char *ptr);
char					*expand_dollar(char *str, char *ptr);
char					*find_dollar(const char *s);
void					handle_expansion(void);
int						handle_shortcuts(char **args);
int						check_cmd(void);
int						print_current_dir_basename(void);
void					free_args(char **args);
char					**split_line_commands(char *line);
void					print_shell_info(void);
void					loop_shell(void);
void					clear_screen(void);
char					*create_filepath(char *path, char *filename, int len);
void					init_shortcuts(void);
void					handle_error(char *message, int reset);
void					set_terminal(char *id);
int						ft_putschar(int c);
void					save_cursor_position(void);
void					restore_terminal_mode(void);
int						lexi(void);
void					create_input_tok(int type, char *str);
t_token					*create_input_token(int type, char *value);
int						list_len_token();

/*
** Move cursor functions
*/
void					move_cursor_right_edge(void);
void					move_cursor_next_line(void);
void					move_cursor_start(void);
void					move_cursor_up(void);
void					move_cursor_down(void);
void					move_cursor_left(void);
void					move_cursor_right(void);
void					move_word_right(void);
void					move_word_left(void);
void					move_cursor(void);
void					cursor_jump_up(int *left_len);

/*
** Handle keys functions
*/
int						handle_keys(void);
int						read_key(void);
char					*str_remove_char(char *str, int index);
char					*str_add_char(char *str, char c);
void					handle_delete(void);
void					handle_backspace(void);
void					handle_control_sequence(char *c);

/*
** History functions
*/
void					get_history_file_path(void);
void					get_history_prev(void);
void					get_history_next(void);
void					open_history_file(void);
void					add_to_history(char *line);
void					save_command_history(void);
int						same_as_previous_command();
void					free_history(void);

/*
** Alias functiuons
*/
void					free_alias(void);
void					free_alias_node(t_alias **head_ref, t_alias *del);
t_alias					*new_alias_node(char **line, t_alias *prev);
void					add_to_alias(char **line);
char					*produce_back_front(char **line, int i, size_t len,
						size_t len2);
char					*value_alias(char *value);
int						len_eql(char *arg);
void					modify_line_with_alias(void);

/*
** Termcaps functions
*/
void					init_termcaps(void);
void					create_terminal_raw_mode();
void					set_terminal_raw_mode(void);

/*
** Signal functions
*/
void					handle_signal_suspend(void);
void					handle_signal_continue(void);
void					handle_signal_interrupt(void);
void					handle_signal_resize(void);
void					handle_signal(int sig);
void					restore_signals(void);
void					init_signal_handling(void);
int						get_input();
void					check_str(void);
void					find_prompt_y(void);
void					init_key_sequences();
char					*str_add_str(char *str, char *str2);
int						init_ast_execution(t_ast *ast);
int						check_syntax(t_token *token);
void					print_input();
int						input_too_large(void);
int						filename_character_allowed(char c);

/*
** Copy paste cut functions
*/
void					copy_start();
void					paste();
void					cut(void);
void					cut_new_line(int len);
char					*str_add_paste(char *str, char *paste);

/*
** Autocomplete functions
*/
void					autocomplete(char **line, char previous_pressed_key);
void					get_autocomplete_commands(void);
int						filename_character_allowed(char c);
void					copy_and_escape_characters(char *dst, char *src);
t_autocomp				*autocomp_new_command(char *command);
void					autocomp_append_command(char *command);
void					autocomp_commands_append_dir(char *path);
void					autocomplete_from_path(void);
void					free_autocomp_commands();
void					autocomplete_from_path(void);
void					print_autocomp_commands(void);

/*
** Commands & reddirections
*/
void					run_commands(void);
void					run_commands_group(t_command *commands);
t_command				*get_commands(void);
t_command				*get_next_command(void);
void					print_commands(t_command *commands);
size_t					commands_amount(t_command *commands);

int						check_token_fd_aggregation();
void					add_redir(t_command *command, int aggregation);
int						check_token_redir();
void					add_arg(t_command *command);
int						ft_nbrlen(int nbr);
int						*get_pipes(t_command *commands);
size_t					commands_amount(t_command *commands);
int						execute_command(t_command *command, int *pipes,
						int command_num);
void					execute_builtin_in_parent(t_command *command);
void					child_execute_command(t_command *command,
						int *pipes, int command_num);
char					**command_arguments_to_arr(t_command *command);
void					handle_redirections(t_command *command);
void					handle_binaries(char **args);
void					pipe_input(int *pipes, int command_num);
void					pipe_output(int *pipes, int command_num);
void					close_pipes(int *pipes);
void					check_file_descriptors_valid(char *word1, char *word2);
int						string_is_number(char *str);
char					*get_partial_command(char *line);
char					**get_matching_commands(char *part_command);
int						find_start_of_command_index(char *str, int end_index);
void					complete_command(char **line,
						char previous_pressed_key, char **matching_commands);
DIR						*open_dir_until_last_slash(char *path);
char					**get_dir_commands(char *path);
int						check_command_valid_dir(char *command);

/*
** Redirect functions
*/
void					redirect_output_to_file_truncate(char *file);
void					redirect_fd_to_fd(char *word1, char *word2, int type);
void					redirect_output_to_file_append(char *file);
void					redirect_file_to_input(char *file);
void					redirect_heredoc_to_input(char *eof);

/*
** Heredoc functions
*/
int						get_heredoc_input(char **line);
void					save_cursor_position_heredoc();
int						handle_keys_heredoc(char **line,
						char *previous_pressed_key);
int						input_too_large_heredoc(char **line);
void					print_input_heredoc(char *line);
void					handle_control_sequence_heredoc(char **line, char *c);
void					handle_backspace_heredoc(char **line);
void					cursor_jump_up_heredoc(char *line, int *left_len);
void					find_prompt_y_heredoc(char *line);
void					move_cursor_heredoc(char *line);
void					move_cursor_start_heredoc(void);
void					move_cursor_next_line_heredoc(char *line);
void					move_cursor_down_heredoc(void);
void					move_cursor_up_heredoc(char **line);
void					move_word_right_heredoc(char **line);
void					move_word_left_heredoc(char **line);
void					move_cursor_right_heredoc(void);
void					move_cursor_left_heredoc(char **line);
void					move_cursor_newline();
void					get_history_next_heredoc(char **line);
void					get_history_prev_heredoc(char **line);
void					handle_delete_heredoc(char **line);
char					*str_remove_char_heredoc(char **str, int index);
char					*str_add_char_heredoc(char **str, char c);
char					*token_type_to_char(int type);
int						advance_tokens(void);
void					free_token(t_token *token);
char					*adding_str_to_newstr(char *newstr, char *str,
						int index);
char					*adding_str_to_paste(int index, char *newstr,
						char *str, char *paste);
void					free_paths(char **paths, int i);
int						check_ast(void);

#endif
