/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:24:33 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/14 14:21:06 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (0);
	d = dst;
	s = (unsigned char *)src;
	if (s < d)
	{
		s += len;
		d += len;
		while (len --)
			*--d = *--s;
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
