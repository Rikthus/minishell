/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulipe <tulipe@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 01:15:22 by tulipe            #+#    #+#             */
/*   Updated: 2022/09/27 01:32:47 by tulipe           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	int	option;
	int	i;

	option = 0;
	i = 1;
	if (argc > 1)
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
	return (0);
}