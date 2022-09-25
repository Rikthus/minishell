/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sap <sap@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:17:20 by maxperei          #+#    #+#             */
/*   Updated: 2022/01/26 14:13:48 by sap              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_strlen_n(char *str, int n)
{
	int	i;

	i = 0;
	if (!n)
		while (str[i])
			i++;
	else
	{
		while (str[i] == '\0' && i < BUFFER_SIZE)
			i++;
		str += i;
		i = 0;
		while (str[i] != '\n' && str[i])
			i++;
		if (str[i] == '\n')
			i++;
	}
	return (i);
}

static	int	ft_cpybuf(char *buf, char *join, int i)
{
	int	j;

	j = 0;
	while (buf[j] == '\0' && j < BUFFER_SIZE)
		j++;
	while (buf[j] != '\n' && buf[j])
	{
		join[i] = buf[j];
		buf[j] = '\0';
		i++;
		j++;
	}
	if (buf[j] == '\n')
	{
		join[i] = buf[j];
		buf[j] = '\0';
		i++;
	}
	return (i);
}

char	*ft_strjoin_n(char *line, char *buf)
{
	char	*join;
	int		i;

	join = malloc(ft_strlen_n(line, 0) + ft_strlen_n(buf, 1) + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (line[i])
	{
		join[i] = line[i];
		i++;
	}
	free(line);
	i = ft_cpybuf(buf, join, i);
	join[i] = '\0';
	return (join);
}
