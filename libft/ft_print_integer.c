/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:45:45 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/22 19:59:59 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putnbr(int nbr)
{
	unsigned int	unbr;

	if (nbr < 0)
	{
		write(1, "-", 1);
		unbr = -nbr;
	}
	else
		unbr = nbr;
	if (unbr > 9)
		ft_putnbr(unbr / 10);
	ft_putchar(unbr % 10 + 48);
}

int	ft_print_integer(va_list ap)
{
	int		len;
	int		nbr;

	nbr = va_arg(ap, int);
	len = ft_nbrlen(nbr);
	if (nbr < 0)
		len++;
	ft_putnbr(nbr);
	return (len);
}
