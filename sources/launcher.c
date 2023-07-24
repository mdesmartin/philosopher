/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/21 10:34:25 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*routine(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->rules->m_all_philo_created);
	pthread_mutex_unlock(&philosopher->rules->m_all_philo_created);
	if (philosopher->id % 2 == 0)
		usleep(2000);
	while (!everyone_eated(philosopher) && no_death(philosopher))
	{
		display_logs(philosopher, "is thinking");
		if (no_death(philosopher))
			eat(philosopher);
		if (no_death(philosopher))
		{
			display_logs(philosopher, "is sleeping");
			philosopher->last_sleep_in_ms = timestamp_in_ms(philosopher->rules);
			p_pause(philosopher, philosopher->last_sleep_in_ms, \
			philosopher->rules->time_to_sleep);
		}
	}
	return (NULL);
}

int	philo_launcher(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->rules.m_all_philo_created);
	while (i < data->rules.nb_of_philo)
	{
		if (pthread_create(&data->philosopher[i].thread, NULL, \
		(void *)&routine, &data->philosopher[i]) != 0)
			return (free_n_destroy(data), \
			display_error("In initializing pthread\n"), 1);
		i++;
	}
	gettimeofday(&data->rules.begin_time, NULL);
	pthread_mutex_unlock(&data->rules.m_all_philo_created);
	i = 0;
	while (i < data->rules.nb_of_philo)
	{
		if (pthread_join(data->philosopher[i].thread, NULL) != 0)
			return (display_error("In joinning pthread\n"), 1);
		i++;
	}
	return (0);
}
