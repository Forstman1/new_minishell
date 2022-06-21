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
			return ;
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
	int	i;

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
	t_token	*token;

	lst = env;
	if (!env)
	{
		ft_putstr_fd("envirement is not set\n", 2);
		status.exit_status = 1;
		return ;
	}
	if (one_cmd(env, arg))
		return ;
	while (token)
	{
		if (token->token == 'c')
		{
			if (cmd_token(token, arg, env))
				return ;
			arg->in_fd = arg->fd[0];
			close(arg->fd[1]);
		}
		else if (token->token == '<')
		{
			if (!access(token->content, X_OK))
			{
				ft_putstr_fd("file not found", 2);
				status.exit_status = 1;
				return ;
			}
			arg->in_fd = open(token->content, O_RDONLY);
			token = token->next;
		}
		else if (token->token == '<<')
		{
			arg->in_fd = open(".infile", O_CREAT | O_RDWR | O_APPEND);
			her_doc(token, arg);
		}
		else
			token = token->next;
	}
}
