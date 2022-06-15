/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_head.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_HEADER_H
# define MS_HEADER_H

/* ---------------------------------- Libraries ----------------------------- */
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/* ----------------------------------- Enums -------------------------------- */
typedef enum e_enum
{
	OPT1,
	OPT2,
	OPT3,
} t_enum;

/* ---------------------------------- TypeDefs ------------------------------ */
typedef unsigned int t_uint;
typedef unsigned long t_ulong;
typedef unsigned char t_uchar;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_token
{
    struct s_token  *prev;
    int             token;
    int             red_from; // redirected from
    char            *content;
    struct s_token  *next;
}    t_token;

typedef struct s_arg
{
	char	**args;
	char	*str;
	char	**paths;
	char	*cmd_path;
	char	**cmd;
	int		fd[2];
	int		in_fd;
	int		i;
} t_arg;


/* ------------------------------ Utils functions ---------------------------- */


void	ft_lstadd_back1(t_env **lst, t_env *new);
t_env	*ft_lstnew1(char *key, char *value);
char	*get_keys(char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp1(char *s1, char *s2);
char	*ft_strrchr1(char *str, int c);
int		ft_strcmp2(char *s1, char *s2);

/* --------------------------------- builtins --------------------------------- */

char	*pwd(t_env *env, int i);
void	export_env(t_env **env, char *str, char **find, t_arg *arg);
int		check_equal(t_env *lst, char *str, t_arg *arg);
void	sorted_env(t_env *lst, t_arg *arg);
void	export_things(t_env *env, char	*find, t_arg *arg);
void	unset_env(t_env **env, char **str);
void	unset_utils(t_env **env, t_env *lst, char *find);
void	env(t_env *env);
void	exit10(void);
void	echo_env1(t_env *env, char **str);

/* --------------------------------- cd not used anymore --------------------------------- */

void	cd_env(t_env *env, char	*str, char *arg);
void	cd_path(t_env *env, char *arg);
void	cd_back(t_env *env, char *arg);
void	cd_home(t_env *env, char *arg);
void	cd_root(t_env *env, char *arg);
void	cd_samdir(t_env *env, char *arg);
void	cd_dash(t_env *env, char *arg);
void	signals(void);

/* --------------------------------- Pipes --------------------------------- */

int		check_keys(t_env *lst, char *str, int *j);
void	check_command(t_env	*env, t_arg *arg);
int		check_path(t_env *env, t_arg *arg);
void	execute_func(t_env	*env, t_arg *arg, t_token *token, int j);
int		check_builtins(t_env	*envi, char *str);
void	builtins(t_env	*envi, char *str, t_arg *arg);
void	check_command(t_env	*env, t_arg *arg);
int		check_cmd(t_env	*env, t_arg *arg, char *str);
void	ft_dup(t_token *token, t_arg *arg, int j);
int		cmd_token(t_token *token, t_arg *arg, t_env *env);
void	execute_func(t_env	*env, t_arg *arg, t_token *token, int j);

#endif 