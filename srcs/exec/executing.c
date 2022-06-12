/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../ms_head.h"


void	execute_func(t_env	*env, t_arg *arg, t_token *token, int j)
{
	int i;

	i = fork();
	if (i == 0)
	{
		if (j == 1)
			ft_dup(token, arg, 1);
		else
			ft_dup(token, arg, 0);
		execve(arg->cmd_path, arg->cmd, arg->paths);
	}
	waitpid(i, NULL, 0);
}

void	her_doc(t_token *token, t_arg *arg)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = NULL;
	tmp = NULL;
	while (1)
	{
		str = readline("");
		if (!ft_strcmp(str, token->content))
		{
			return ;
		}
		else
		{
			ft_putstr_fd(str, arg->in_fd);
			free(str);
			str = NULL;
		}
	}
}

int	one_cmd(t_env	*env, t_arg *arg)
{
	int i;

	i = 0;
	while (arg->args[i])
		i++;
	if (i == 1)
	{
		i = 0;
		if (check_builtins(env, arg->args[i]))
		{
			builtins(env, arg->args[i], arg);
			return (1);
		}
	}
	return (0);
}


void	check_command(t_env	*env, t_arg *arg)
{
	t_env	*lst;
	t_token *token;
	int		i;
	int		id;
	int		j;

	lst = env;
	i = 0;
	id = 0;
	j = 0;
	if (!env)
	{
		ft_putstr_fd("envirement is not set\n", 2);
		return ;
	}
	if (one_cmd(env, arg))
		return ;
	i = 0;
	while (token)
	{
		if (token->token == 'c')
		{
			pipe(arg->fd);
			if (check_builtins(env, token->content))
			{
				id = fork();
				if (id == 0)
				{
					if (token->next != NULL)
						ft_dup(token, arg, 1);
					else
						ft_dup(token, arg, 0);
					builtins(env, token->content, arg);
					close(arg->fd[1]);
					exit(0);
				}
				waitpid(id, NULL, 0);
				close(arg->fd[1]);
				token = token->next;
			}
			else
			{
				if (check_path(env, arg))
					return ;
				j = check_cmd(env, arg, token->content);
				if (j == 1)
				{
					if (token->next != NULL)
						execute_func(env, arg, token, 1);
					else
						execute_func(env, arg, token, 0);
					token = token->next;
				}
				else
					return ;
			}
			arg->in_fd = arg->fd[0];
			close(arg->fd[1]);
		}
		else if (token->token == '<')
		{
			if (!access(token->content, X_OK))
			{
				ft_putstr_fd("file not found", 2);
				return ;
			}
			arg->in_fd = open(token->content, O_RDONLY);
			token = token->next;
		}
		else if (token->token == '<<')
		{
			arg->in_fd = open(".infiles", O_RDWR);
			her_doc(token, arg);
		}
		else
			token = token->next;
	}
}
