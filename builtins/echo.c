/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:15:22 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/29 14:29:26 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//DONE
//NO VERIF
int	ft_echo(char **argv)
{
	int	option;
	int	i;
	int	nb_arg;

	nb_arg = 1;
	while (argv[nb_arg])
		nb_arg++;
	option = 0;
	i = 1;
	if (nb_arg > 1)
	{
		if (ft_strncmp(argv[1], "-n", 3) == 0)
			option = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (EXIT_SUCCESS);
}
