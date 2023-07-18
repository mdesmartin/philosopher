/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:58:17 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 23:45:14 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	free_n_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_of_philo)
	{
		pthread_detach(data->philosopher[i].thread);
		pthread_mutex_destroy(&data->philosopher[i].m_left_fork);
		i++;
	}
	pthread_mutex_destroy(&data->rules.m_one_philo_died);
	pthread_mutex_destroy(&data->rules.m_all_philo_created);
	free_tab((void **)data->philosopher);
}

int main(int argc, char **argv)
{
	t_data data;

	if (!check_arg(argc, argv))
	{
		if (!init_data(&data, argv))
		{
			if (philo_launcher(&data) == 2)
				free_n_destroy(&data);
		}
	}
	return (0);
}

// test 10 410 200 200