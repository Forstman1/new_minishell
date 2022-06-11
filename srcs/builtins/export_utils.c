/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:05:59 by sahafid           #+#    #+#             */
/*   Updated: 2022/05/29 16:06:00 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../ms_head.h"

void	sorted_env(t_env *lst)
{
	char	**keys;
	t_env	*sort;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	sort = lst;
	while (sort)
	{
		i++;
		sort = sort->next;
	}
	keys = (char**)malloc(sizeof(char*) * (i + 1));
	sort = lst;
	i = 0;
	while (sort)
	{
		keys[i] = ft_strdup(sort->key);
		i++;
		sort = sort->next;
	}
	i = 0;
	while (keys[i])
	{
		j = 0;
		while (keys[j])
		{
			if (ft_strcmp2(keys[j], keys[i]) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (keys[i])
	{
		sort = lst;
		while (sort)
		{
			if (!ft_strcmp(keys[i], sort->key))
			{
				printf("declare -x %s=\"%s\"\n", keys[i], sort->value);
				break ;
			}
			sort = sort->next;
		}
		i++;
	}
	while (keys[i])
	{
		free(keys[i]);
		i++;
	}
	free(keys);
}