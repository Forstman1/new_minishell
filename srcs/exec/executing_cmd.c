/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_cmd.c                                    :+:      :+:    :+:   */
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

void	executing_builtins(t_token *token, t_arg *arg, t_env *env)
{
	int id;

	id = 0;
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

int	cmd_token(t_token *token, t_arg *arg, t_env *env)
{
	int	j;

	pipe(arg->fd);
	if (check_builtins(env, token->content))
		executing_builtins(token, arg, env);
	else
	{
		if (check_path(env, arg))
			return (1);
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
			return (1);
	}
	return (0);
}

