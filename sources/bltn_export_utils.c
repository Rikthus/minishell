/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:12:25 by maxperei          #+#    #+#             */
/*   Updated: 2022/10/04 18:17:34 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_big(char ***big, char *target)
{
	big[0][0] = target;
	big[0][1] = target;
	big[0][2] = NULL;
}

int	export_no_option(void)
{
	ft_putstr_fd("export: no options handled\n", 2);
	return (EXIT_FAILURE);
}
