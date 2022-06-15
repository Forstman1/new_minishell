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

void	sorted_env(t_env *lst, t_arg *arg)
{
	t_env	*sort;
	char	*tmp;
	char	**keys;
	int		i;
	int		j;

	i = 0;
	sort = lst;
	while (sort)
	{
		i++;
		sort = sort->next;
	}
	keys = (char **)malloc(sizeof(char *) * (i + 1));
	sort = lst;
	i = 0;
	while (sort)
	{
		if (sort->key != NULL)
			keys[i] = ft_strdup(sort->key);
		else
			keys[i] = NULL;
		i++;
		sort = sort->next;
	}
	keys[i] = NULL;
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
				if (sort->value == NULL)
					printf("declare -x %s\n", keys[i]);
				else
					printf("declare -x %s=\"%s\"\n", keys[i], sort->value);
				break ;
			}
			sort = sort->next;
		}
		i++;
	}
	i = 0;
	while (keys[i])
	{
		free(keys[i]);
		i++;
	}
	free(keys);
}
