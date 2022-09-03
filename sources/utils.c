/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:08:57 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/03 22:41:38 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*free_split_error(char **array, int nb_pointer)
{
	while (nb_pointer > -1)
	{
		free(array[nb_pointer]);
		nb_pointer--;
	}
	free(array);
	return (NULL);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;	
	}
	free (array);
}

void	change_quote_state(char quote, t_state *state)
{
	if (quote == '\'' && state->dq == OFF)
	{
		if (state->sq == OFF)
			state->sq = ON;
		else
			state->sq = OFF;
	}
	else if (quote == '\"' && state->sq == OFF)
	{
		if (state->dq == OFF)
			state->dq = ON;
		else
			state->dq = OFF;
	}
}