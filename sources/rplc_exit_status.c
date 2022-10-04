/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rplc_exit_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxperei <maxperei@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 03:25:10 by tulipe            #+#    #+#             */
/*   Updated: 2022/10/04 18:29:46 by maxperei         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	status_len(void)
{
	int	tmp_status;
	int	len;

	tmp_status = g_shell.exit_status;
	len = 0;
	if (tmp_status == 0)
		return (1);
	if (tmp_status < 0)
		len++;
	while (tmp_status != 0)
	{
		tmp_status /= 10;
		len++;
	}
	return (len);
}

static	void	cpy_exit(char **str_exit, int tmp_status, int i)
{
	str_exit[0][i] = '\0';
	if (tmp_status == 0)
		str_exit[0][0] = '0';
	if (tmp_status < 0)
	{
		tmp_status *= -1;
		str_exit[0][0] = '-';
	}
	if (tmp_status > 0)
	{
		while (tmp_status != 0)
		{
			i--;
			str_exit[0][i] = tmp_status % 10 + 48;
			tmp_status /= 10;
		}
	}
}

static	char	*fill_str_exit(void)
{
	int		tmp_status;
	int		i;
	char	*str_exit;

	tmp_status = g_shell.exit_status;
	i = status_len();
	str_exit = malloc(sizeof(char) * (i + 1));
	if (!str_exit)
		return (NULL);
	cpy_exit(&str_exit, tmp_status, i);
	return (str_exit);
}

int	replace_exit_status(char **str, t_expan exp)
{
	if (!init_exp(str, &exp))
		return (0);
	exp.var_dup = fill_str_exit();
	if (!(exp.var_dup))
	{
		free_expan(&exp);
		return (0);
	}
	if (!join_all(str, exp))
		return (0);
	return (1);
}
