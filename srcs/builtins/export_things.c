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


int check_equal(t_env *lst, char *str, t_arg *arg)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	add_to_export(char	*str, t_arg *arg)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (arg->keys[i])
		i++;
	tmp = arg->keys;
	arg->keys = malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (tmp[i])
	{
		arg->keys[i] = tmp[i];
		i++;
	}
	arg->keys[i] = str;
	arg->keys[i + 1] = NULL;
	return ;
}

void	export_things(t_env *env, char	*find, t_arg *arg)
{
	int		i;
	int		j;
	t_env	*lst;
	char	*tmp;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	key = NULL;
	value = NULL;
	lst = env;
	if (check_keys(lst, find))
		return ;
	if (check_equal(lst, find, arg))
		add_to_export(find, arg);
	else
	{
		while (find[i])
		{
			if (find[i] == '=')
			{
				if (find[i - 1] == '+' && find[i - 2] != '+')
					j = 1;
				else if (find[i - 1] == '-')
				{
					ft_putstr_fd("Error\n", 2);
					return ;
				}
				break ;
			}
			i++;
		}
		if (i == ft_strlen(find))
			return ;
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
			lst = ft_lstnew1(key, value);
			ft_lstadd_back1(&env, lst);
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
			lst = ft_lstnew1(key, value);
			ft_lstadd_back1(&env, lst);
		}
	}
}