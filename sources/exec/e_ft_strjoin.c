/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_ft_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:20:25 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/11/29 19:26:29 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_mini(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*c;
	int		t;

	i = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	t = (ft_strlen((char *)s1) + ft_strlen((char *)s2));
	c = malloc(sizeof(char) * (t + 1));
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i ++;
	}
	while (s2[k])
	{
		c[i++] = s2[k++];
	}
	c[i] = '\0';
	return (c);
}
