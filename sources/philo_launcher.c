/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/19 18:03:34 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

//fork only used to eat, so free to use when think and sleep
//when each time to eat reach or when one philo die, sim end
//each philo got a number betwen 1 and nb_philo

// tant que tous les philos sont en vie faire la routine sinon stop, clean and free and destroy tout, pour savoir si en vie wait une valeur de retour ?

void	*routine(t_philosopher *philosopher)
{	
	pthread_mutex_lock(&philosopher->rules->m_all_philo_created);
	pthread_mutex_unlock(&philosopher->rules->m_all_philo_created);
	// if (philosopher->id == 1)
	// 	printf("left %p\n", &philosopher->m_left_fork);
	// if (philosopher->id == 10)
	// 	printf("right %p\n", &philosopher->m_right_fork);
	if (philosopher->id % 2 == 0)
		usleep(2000);//jusqua 60k
	while (!everyone_eated(philosopher) && no_death(philosopher))
	{
		display_logs(philosopher, "is thinking");
		if (no_death(philosopher))
			eat(philosopher);
		if (no_death(philosopher))
		{
			display_logs(philosopher, "is sleeping");
			philosopher->last_sleep_in_ms = timestamp_in_ms(philosopher->rules);
			philo_pause(philosopher, philosopher->last_sleep_in_ms, philosopher->rules->time_to_sleep);
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
		if (pthread_create(&data->philosopher[i].thread, NULL, (void *)&routine, &data->philosopher[i]) != 0)
			return (1);
		i++;
	}
	gettimeofday(&data->rules.begin_time, NULL);
	pthread_mutex_unlock(&data->rules.m_all_philo_created);
	i = 0;
	while (i < data->rules.nb_of_philo)
	{
		if (pthread_join(data->philosopher[i].thread, NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}
