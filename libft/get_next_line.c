/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sap <sap@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:08:00 by maxperei          #+#    #+#             */
/*   Updated: 2022/01/26 14:14:49 by sap              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///////////  CHECK IF BUFFER IS NOT EMPTY  ////////////

static	int	ft_checkbuf(char *buf)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buf[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

/////////////  CHECK IF '\n' IN LINE  ////////////////

static	int	ft_islinedone(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

/////////////////////  READER  ///////////////////////

static	char	*ft_reader(int fd, char *line, char *buf)
{
	int	bytes;

	while (!ft_islinedone(line))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(line);
			return (NULL);
		}
		line = ft_strjoin_n(line, buf);
		if (!line)
			return (NULL);
		if (*line == '\0' && bytes == 0)
		{
			free(line);
			return (NULL);
		}
		else if (bytes == 0)
			return (line);
	}
	return (line);
}

/////////////////  CONTROL FUNCTION  //////////////////

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1] = {{0}};

	if (BUFFER_SIZE < 1 || fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	if (ft_checkbuf(buf[fd]))
		line = ft_strjoin_n(line, buf[fd]);
	line = ft_reader(fd, line, buf[fd]);
	return (line);
}
