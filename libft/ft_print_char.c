/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:45:38 by maxperei          #+#    #+#             */
/*   Updated: 2022/04/22 19:59:24 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(va_list ap)
{
	int		c;
	char	cc;

	c = va_arg(ap, int);
	cc = c;
	write(1, &cc, 1);
	return (1);
}
