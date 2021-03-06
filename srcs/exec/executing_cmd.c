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

void	execute_func(t_env	*env, t_arg *arg, t_shell *shell, int j)
{
	int	i;

	i = fork();
	if (i == 0)
	{
		if (j == 1)
			ft_dup(shell, arg, 1);
		else
			ft_dup(shell, arg, 0);
		execve(shell->data, shell->switchs, arg->paths);
		if (errno == EACCES || errno == EFAULT)
			exit(127);
	}
	waitpid(i, &status.exit_status, 0);
	if (WIFEXITED(status.exit_status))
        status.exit_status = status.exit_status % 255;
    else if (WIFSIGNALED(status.exit_status))
        status.exit_status += 128;
}

void	executing_builtins(t_shell *shell, t_arg *arg, t_env *env)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		if (shell->next != NULL)
			ft_dup(shell, arg, 1);
		else
			ft_dup(shell, arg, 0);
		builtins(env, shell->data, arg);
		close(arg->fd[1]);
		exit(0);
	}
	waitpid(id, NULL, 0);
	close(arg->fd[1]);
	shell = shell->next;
}

int	cmd_token(t_shell *shell, t_arg *arg, t_env *env)
{
	int	j;

	pipe(arg->fd);
	if (check_builtins(env, shell->data))
		executing_builtins(shell, arg, env);
	else
	{
		j = check_cmd(env, arg, shell->data);
		if (j == 1)
		{
			if (shell->next != NULL)
				execute_func(env, arg, shell, 1);
			else
				execute_func(env, arg, shell, 0);
			shell = shell->next;
		}
		else
		{
			close(arg->fd[0]);
			close(arg->fd[1]);
			return (1);
		}
	}
	return (0);
}
