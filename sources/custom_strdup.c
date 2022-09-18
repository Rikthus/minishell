/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:10:43 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/18 14:57:17 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*custom_strdup(char *str, int start, int end)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * ((end - start) + 2));
	if (!dup)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		dup[i] = str[start];
		start++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
