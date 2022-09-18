/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:08:56 by maxperei          #+#    #+#             */
/*   Updated: 2021/11/14 14:21:38 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_counter(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		len++;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

// change for (nbr > 9)
static	char	*make_str(char *str, long nbr, int len)
{
	len--;
	if (nbr < 0)
	{
		nbr = -nbr;
		while (len > 0)
		{
			str[len] = nbr % 10 + 48;
			nbr /= 10;
			len--;
		}
		str[len] = '-';
	}
	else
	{
		while (len >= 0)
		{
			str[len] = nbr % 10 + 48;
			nbr /= 10;
			len--;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nbr;
	char	*str;

	len = ft_counter(n);
	str = malloc((len + 1) * sizeof(*str));
	if (!str)
		return (0);
	nbr = n;
	str[len] = '\0';
	return (make_str(str, nbr, len));
}
