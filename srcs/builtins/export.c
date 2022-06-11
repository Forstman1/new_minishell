/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:05:59 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:06:00 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../ms_head.h"


int	check_keys(t_env *lst, char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (0);
	ft_putstr_fd("error", 2);
	return (1);
}



void	export_env(t_env **env, char *str, char *find)
{
	t_env	*lst;
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lst = *env;
	if (!find)
	{
		sorted_env(lst);
		return ;
	}
	else
		export_things(lst, find, key, value);
}


void	export_env(t_env **env, char *str, char **find)
{
	t_env	*lst;
	int		i;

	i = 1;
	lst = *env;
	if (!find[1])
	{
		sorted_env(lst);
		return ;
	}
	else
	{
		while (find[i])
		{
			export_utils(*env, str, find[i]);
			i++;
		}
	}
}
