/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:58:17 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/24 16:21:41 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc > 6 || argc < 5)
	{
		display_error("please complete arguments with number_of_");
		ft_putstr_fd("philosophers time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
		return (1);
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || argv[i][j] <= 0)
				return (display_error("one arg is not a valid number\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_arg(argc, argv))
	{
		if (!init_data(&data, argv))
		{
			if (!philo_launcher(&data))
				free_n_destroy(&data);
		}
	}
	return (0);
}
