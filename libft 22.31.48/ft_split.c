/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:19:42 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/14 15:45:26 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

static char	*ft_strcdup(char *str, char c)
{
	size_t	i;
	char	*dup;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	dup = malloc((i + 1) * sizeof (*dup));
	if (!dup)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static size_t	word_count(char const *s, char c)
{
	size_t	nb_words;
	size_t	i;

	nb_words = 0;
	if (s[0] != c)
		nb_words++;
	i = 1;
	while (s[i])
	{
		if ((s[i - 1] == c) && (s[i] != c))
			nb_words++;
		i++;
	}
	return (nb_words);
}

static	char	**make_split(char const *s, char c, char **array)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			array[i] = ft_strcdup((char *)s, c);
			if (!array[i])
				return (ft_free(array));
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	array[i] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_words;
	char	**array;

	if (s[0] == 0)
	{
		array = malloc(1 * sizeof(*array));
		if (!array)
			return (0);
		array[0] = 0;
		return (array);
	}
	nb_words = word_count(s, c);
	array = malloc((nb_words + 1) * sizeof(*array));
	if (!array)
		return (0);
	return (make_split(s, c, array));
}

// int split()
// {
// 	len = countwords;
// 	tab = malloc(countwords)
// 	while (i < countwords)
// 		tab[i] = get_next_words()
// 			tab[i] = 0;
// }
