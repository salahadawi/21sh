/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:36:53 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:32:15 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "sh.h"

# define INIT_SIZE 7
# define MAX_HASH 3

typedef struct			s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
	int					count;
	char				pad[4];
}						t_hash_item;

typedef struct			s_hashmap
{
	t_hash_item			**items;
	int					size;
	char				pad[4];
}						t_hashmap;

typedef struct			s_hash_args
{
	char				*path;
	int					name_index;
	unsigned char		state;
	unsigned char		opt;
	char				pad[2];
}						t_hash_args;

typedef enum			e_hash_opt
{
	o_l = 0B1,
	o_d = 0B10,
	o_r = 0B100
}						t_hash_opt;

typedef enum			e_hash_state
{
	get_opt,
	get_hash_path,
	get_name,
	get_done
}						t_hash_state;

typedef enum			e_hashopt
{
	hash_check,
	hash_exec,
	hash_reset
}						t_hashopt;

int						hash_builtin(int argc, char **args);
void					print_hashmap(t_hashmap *hashmap);
int						print_invalid_option(char c);
void					delete_map(t_hashmap *hashmap);
int						reset_hash(t_hashmap **hashmap);
int						addto_hashmap(char *key, char *value,
						t_hashmap **hashmap);
int						replace_item(t_hash_item *item, const char *value);
t_hash_item				*create_item(const char *key, const char *value);
int						get_new_prime(int nb);
char					**get_paths(void);
int						addto_hashmap(char *key, char *value,
						t_hashmap **hashmap);
t_hashmap				*grow_up(t_hashmap *previous);
char					*check_map(const char *key, t_hashmap *hashmap,
						t_hashopt opt);
int						drop_item(const char *key, t_hashmap *hashmap);
void					delete_item(t_hash_item *item);
char					*find_path(const char *file, char **paths);
int						hash_print(t_hashmap *hashmap, t_hash_args *hash_args,
						int argc, char **args);
void					map_copy(t_hashmap *previous, t_hashmap **new);
t_hashmap				*init_hashmap(int size);
unsigned int			hashing(const char *key);
int						get_args(char **args, t_hash_args *hash_args);
char					**get_paths(void);

#endif
