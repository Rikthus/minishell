/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:17:20 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/11 16:34:33 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*sub;

	size = ft_strlen(&s[start]);
	if (size > len)
		size = len;
	sub = malloc((size + 1) * sizeof(*sub));
	if (!sub)
		return (0);
	i = 0;
	while (i < len && !(start >= ft_strlen(s)))
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
