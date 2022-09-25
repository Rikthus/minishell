/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:03:33 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/11 17:52:46 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	if (size == 0)
		return (ft_substr(s1, 0, size));
	size--;
	while (&*s1 != &s1[size] && ft_strchr(set, s1[size]))
		size--;
	return (ft_substr(s1, 0, size + 1));
}
