/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:15:22 by tulipe            #+#    #+#             */
/*   Updated: 2022/11/29 19:24:51 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	check_option(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] != '-')
			return (0);
		if (i != 0 && str[i] != 'n')
			return (0);
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static	int	print_start(char **argv, int *option)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (check_option(argv[i]) == 1)
			*option = 1;
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] != '-' ||
				(j > 0 && argv[i][0] == '-' && argv[i][j] != 'n'))
				return (i);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	option;
	int	nb_arg;

	option = 0;
	nb_arg = 1;
	while (argv[nb_arg])
		nb_arg++;
	if (nb_arg > 1)
		nb_arg = print_start(argv, &option);
	else
		nb_arg = 1;
	while (argv[nb_arg])
	{
		ft_putstr_fd(argv[nb_arg], 1);
		nb_arg++;
		if (argv[nb_arg])
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
