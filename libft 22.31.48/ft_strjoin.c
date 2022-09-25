/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:39:32 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/11 16:34:01 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*join;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(len * sizeof(*join));
	if (!join)
		return (0);
	if (ft_strlcpy(join, s1, len) >= 0 && ft_strlcat(join, s2, len) >= 0)
		return (join);
	else
		return (0);
}
