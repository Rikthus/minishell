/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:37:21 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/08 14:39:08 by tulipe           ###   ########lyon.fr   */
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
