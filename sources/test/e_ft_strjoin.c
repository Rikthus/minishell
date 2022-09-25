/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_ft_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:20:25 by cdutel-l          #+#    #+#             */
/*   Updated: 2022/09/18 15:08:33 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
