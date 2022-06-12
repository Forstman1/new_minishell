/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:08:22 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:08:23 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../ms_head.h"

void	ft_dup(t_token *token, t_arg *arg, int j)
{
	int fd;

	if (j == 1)
	{
		if (token->next->token == '>')
		{
			fd = open(token->next->content, O_CREAT | O_WRONLY | O_TRUNC);
			dup2(fd, 1);
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
		else if (token->next->token == '>>')
		{
			fd = open(token->next->content, O_CREAT | O_WRONLY | O_APPEND);
			dup2(fd, 1);
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
		else
		{
			dup2(arg->fd[1], 1);
			dup2(arg->in_fd, 0);
			close(arg->fd[1]);
		}
	}
	else
		dup2(arg->in_fd, 0);
}