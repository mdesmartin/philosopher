/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:11:58 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/20 13:24:39 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	print_error(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc > 6 || argc < 5)
		return (print_error("please complete arguments with : \
		number_of_philosophers time_to_die time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat]\n"));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || argv[i][j] <= 0)
				return (print_error("one arg is not a valid number\n"));
			j++;
		}
		i++;
	}
	return (0);
}
