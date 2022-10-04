/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel-l <cdutel-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:18:11 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/04 14:02:36 by cdutel-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	is_valid_exit(char *exit)
{
	int	i;

	i = 0;
	if (exit[i] == '+' || exit[i] == '-')
		i++;
	while (exit[i])
	{
		if (!ft_isdigit(exit[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (i == 1 && (exit[0] == '+' || exit[0] == '-'))
		return (EXIT_FAILURE);
	if (i > 19)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_exit(char **argv)
{
	int					i;
	unsigned char		exit_value;

	i = 0;
	while (argv[i])
		i++;
	if (argv[1] && is_valid_exit(argv[1]) == EXIT_FAILURE)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_value = 255;
	}
	else if (i > 2)
	{
		exit_value = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
	else if (i == 2)
		exit_value = (unsigned char) ft_atoi(argv[1]);
	else
		exit_value = 0;
	exit(exit_value);
	return (exit_value);
}
