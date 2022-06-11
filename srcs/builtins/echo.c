/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:19:33 by            #+#    #+#             */
/*   Updated: 2022/05/27 18:19:36 by           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ms_head.h"

void	echo_env(t_env *env, char **str)
{
	int		i;
	int		j;
	t_env	*lst;

	i = 1;
	j = 0;
	lst = env;
	if (!str[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		while (str[1][i])
		{
			if (str[1][i] == 'n')
				i++;
			else
			{
				i = 1;
				while (str[i])
				{
					printf("%s", str[i]);
					i++;
				}
			}
		}
		if (str[1][i] == '\0')
		{
			i = 2;
			while (str[i])
			{
				printf("%s", str[i]);
				i++;
			}
		}
	}
	i = 1;
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
	}
}
