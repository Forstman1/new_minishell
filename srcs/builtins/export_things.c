/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:05:59 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:06:00 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ms_head.h"

int	check_equal(t_env *lst, char *str, t_arg *arg)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	export_things(t_env *env, char	*find, t_arg *arg)
{
	int		i;
	int		j;
	t_env	*lst;
	t_env	*lst1;
	char	*tmp;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	key = NULL;
	value = NULL;
	lst1 = NULL;
	lst = env;
	if (check_keys(lst, find, &j, i))
		return ;
	else
	{
		while (lst)
		{
			if (!ft_strncmp(lst->key, find, ft_strlen(lst->key)))
			{
				if (j == 1)
				{
					tmp = lst->value;
					lst->value = ft_strjoin(lst->value, ft_strchr(find, '=') + 1);
					if (tmp != NULL)
						free(tmp);
				}
				else
					lst->value = ft_strchr(find, '=') + 1;
				if (!lst->value)
					lst->value = NULL;
				return ;
			}
			lst = lst->next;
		}
		if (j == 1)
		{
			value = ft_strdup(ft_strchr(find, '=') + 1);
			key = ft_strdup(get_keys(find, '='));
			key = get_keys(key, '+');
			i = 0;
			while (key[i])
			{
				if (key[i] == '+' || key[i] == '-')
				{
					ft_putstr_fd("error\n", 2);
					free(key);
					free(value);
					return ;
				}
				i++;
			}
			lst1 = ft_lstnew1(key, value);
			ft_lstadd_back1(&env, lst1);
		}
		else
		{
			value = ft_strdup(ft_strchr(find, '=') + 1);
			key = ft_strdup(get_keys(find, '='));
			i = 0;
			while (key[i])
			{
				if (key[i] == '+' || key[i] == '-')
				{
					ft_putstr_fd("error\n", 2);
					free(key);
					free(value);
					return ;
				}
				i++;
			}
			lst1 = ft_lstnew1(key, value);
			ft_lstadd_back1(&env, lst1);
		}
	}
}
