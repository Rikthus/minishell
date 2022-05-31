/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:45:27 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/22 20:01:14 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_unbrlen(unsigned int unbr)
{
	int	len;

	len = 0;
	if (unbr == 0)
		return (1);
	while (unbr != 0)
	{
		unbr = unbr / 10;
		len++;
	}
	return (len);
}

static	void	ft_putunbr(unsigned int unbr)
{
	if (unbr > 9)
		ft_putunbr(unbr / 10);
	ft_putchar(unbr % 10 + 48);
}

int	ft_print_unsigned(va_list ap)
{
	int				len;
	unsigned int	unbr;

	unbr = va_arg(ap, unsigned int);
	len = ft_unbrlen(unbr);
	ft_putunbr(unbr);
	return (len);
}
