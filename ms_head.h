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
# include <errno.h>
# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/* ----------------------------------- Enums -------------------------------- */

typedef enum s_type
{
    CMD,
    CMD_NOT_FOUND,
    HERE_DOC,
    RED_IN,
    RED_APPEND,
    RED_OUT,
    PIPE,
    WORD,
    SPACE,
}    t_type;

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

typedef struct s_global
{
	int	exit_status;
} t_global;

t_global status;

typedef struct s_shell
{
    struct s_shell  *prev;
    int             token; // token that tells you wather it's command or operator etc ..
    char            *data; // data that contains command and it's path (e.g /bin/ls) or here-doc delemiter, defult value NULL
    char            **switchs; // switchs that contains command and its switchs (e.g ls, -la ...), defult value NULL
    int                file; // contains file descriptor if token is one of the operators that takes file, defult value -1
    struct s_shell  *next;
}    t_shell;

typedef struct s_arg
{
	char	*str;
	char	**paths;
	char	*cmd_path;
	int		fd[2];
	int		in_fd;
	int		out_fd;
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
void	check_oldpwd(t_env *env, char	*oldpwd);

/* --------------------------------- builtins --------------------------------- */

void	builtins(t_env	*envi, char *str, t_arg *arg);
char	*pwd(t_env *env, int i);
void	unset_env(t_env **env, char **str);
void	unset_utils(t_env **env, t_env *lst, char *find);
void	env(t_env *env);
void	exit10(void);
void	exit11(int	i);
void	echo_env1(t_env *env, char **str);
void	cd_home(t_env *env, char *arg);
void	cd_env(t_env *env, char	*str, char *arg);

/* --------------------------------- cd not used anymore --------------------------------- */

void	cd_path(t_env *env, char *arg);
void	cd_back(t_env *env, char *arg);
void	cd_root(t_env *env, char *arg);
void	cd_samdir(t_env *env, char *arg);
void	cd_dash(t_env *env, char *arg);

/* --------------------------------- export --------------------------------- */

void	export_things(t_env *env, char	*find, t_arg *arg);
void	export_env(t_env **env, char *str, char **find, t_arg *arg);
int		check_equal(t_env *lst, char *str, t_arg *arg);
void	sorted_env(t_env *lst, t_arg *arg);

/* --------------------------------- duping --------------------------------- */

void	ft_dup(t_shell *shell, t_arg *arg, int j);

/* ------------------------- executing function ----------------------------- */

int	one_cmd(t_env	*env, t_arg *arg, t_shell *shell);

int		check_builtins(t_env	*envi, char *str);
void	check_command(t_env	*env, t_arg *arg, t_shell *shell);
int		check_cmd(t_env	*env, t_arg *arg, char *str);
int		cmd_token(t_shell *shell, t_arg *arg, t_env *env);
int		check_keys(t_env *lst, char *str, int *j, int i);
int		check_path(t_env *env, t_arg *arg);
void	execute_func(t_env	*env, t_arg *arg, t_shell *shell, int j);
void	signals(void);

/* ------------------------------------------------------------------------- */

#endif 