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

void	her_doc(t_shell *shell, t_arg *arg)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = NULL;
	tmp = NULL;
	i = open("tmp", O_CREAT | O_WRONLY | O_APPEND);
	while (1)
	{
		str = readline("<< ");
		if (!ft_strcmp(str, shell->data))
		{
			free(str);
			return ;
		}
		else if (!str)
			return ;
		else
		{
			ft_putstr_fd(str, i);
			ft_putstr_fd("\n", i);
			free(str);
			str = NULL;
		}
	}
	close(i);
}

int	one_cmd(t_env	*env, t_arg *arg, t_shell *shell)
{
	int		i;
	t_shell	*lst;

	i = 0;
	lst = shell;
	while (lst)
	{
		if (lst->token == PIPE)
			i++;
	}
	if (i == 0)
	{
		lst = shell;
		if (lst->token == RED_IN)
		{
			arg->in_fd = lst->file;
			lst = lst->next;
		}
		if (check_builtins(env, lst->data))
		{
			if (lst->next != NULL)
				ft_dup(lst, arg, 1);
			else
				ft_dup(lst, arg, 0);
		}
		return (1);		
	}
	return (0);
}

void	check_command(t_env	*env, t_arg *arg, t_shell *shell)
{
	if (one_cmd(env, arg, shell))
		return ;
	if (!env)
	{
		ft_putstr_fd("envirement is not set\n", 2);
		status.exit_status = 1;
		return ;
	}
	while (shell)
	{
		if (shell->token == CMD)
		{
			if (cmd_token(shell, arg, env))
				return ;
			arg->in_fd = arg->fd[0];
			close(arg->fd[1]);
		}
		else if (shell->token == RED_IN)
			arg->in_fd = shell->file;
		else if (shell->token == HERE_DOC)
		{
			her_doc(shell, arg);
			arg->in_fd = open("tmp", O_RDONLY);
		}
		shell = shell->next;
	}
}
