/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:45:50 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/22 20:00:22 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_hexlen(unsigned long long hex)
{
	int	len;

	if (hex == 0)
		return (1);
	len = 0;
	while (hex != 0)
	{
		hex /= 16;
		len++;
	}
	return (len);
}

static	void	ft_puthex(unsigned long long unbr)
{
	if (unbr > 15)
		ft_puthex(unbr / 16);
	ft_putchar("0123456789abcdef"[unbr % 16]);
}

int	ft_print_pointer(va_list ap)
{
	int					len;
	unsigned long long	p;

	len = 2;
	ft_putstr("0x");
	p = va_arg(ap, unsigned long long);
	len += ft_hexlen(p);
	ft_puthex(p);
	return (len);
}
