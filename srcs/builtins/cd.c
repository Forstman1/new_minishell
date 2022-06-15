/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:07:37 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:07:38 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ms_head.h"

void	check_oldpwd(t_env *env, char	*oldpwd)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (!ft_strcmp(lst->key, "OLDPWD"))
		{
			if (oldpwd != NULL)
				lst->value = oldpwd;
			else
				lst->value = "";
			return ;
		}
		lst = lst->next;
	}
	lst = ft_lstnew1("OLDPWD", "");
	ft_lstadd_back1(&env, lst);
}

int	check_cases(t_env *env, char *arg, char *dir, char *oldpwd)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = env;
	dir = NULL;
	if (chdir(arg))
	{
		printf("not sush directory\n");
		return (1);
	}
	while (lst)
	{
		if (!ft_strcmp(lst->key, "PWD"))
		{
			if (lst->value)
				oldpwd = lst->value;
			lst->value = getcwd(dir, 9999);
			i = 1;
			break ;
		}
		lst = lst->next;
	}
	if (i == 0)
	{
		lst = ft_lstnew1("PWD", getcwd(dir, 9999));
		ft_lstadd_back1(&env, lst);
	}
	check_oldpwd(env, oldpwd);
	return (0);
}

void	cd_env(t_env *env, char	*str, char *arg)
{
	t_env	*lst;
	char	*dir;
	char	*oldpwd;
	int		i;

	lst = env;
	dir = NULL;
	oldpwd = NULL;
	i = 0;
	if (!ft_strcmp(arg, NULL))
		cd_home(env, arg);
	else
	{
		if (check_cases(env, arg, dir, oldpwd))
			return ;
	}
}
