/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:08:57 by tulipe            #+#    #+#             */
/*   Updated: 2022/08/31 18:41:29 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			state->dq = ON;
	}
}