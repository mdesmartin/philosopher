/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/19 13:09:38 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

//fork only used to eat, so free to use when think and sleep
//when each time to eat reach or when one philo die, sim end
//each philo got a number betwen 1 and nb_philo

// tant que tous les philos sont en vie faire la routine sinon stop, clean and free and destroy tout, pour savoir si en vie wait une valeur de retour ?

int	everyone_eated(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	if (philosopher->rules->must_eat_time == 0)
		return (0);
	while (i < philosopher->rules->nb_of_philo)
	{
		if (philosopher->nb_of_meals < philosopher->rules->must_eat_time)
			return (0);
		i++;
	}
	return (1);
}

void	check_death(t_philosopher *philosopher)
{
	if (timestamp_in_ms(philosopher->rules) == 0)
		return ; 
	if (timestamp_in_ms(philosopher->rules) - philosopher->last_meal_in_ms >= philosopher->rules->time_to_die)
	{
		pthread_mutex_lock(&philosopher->rules->m_one_philo_died);
		if (philosopher->rules->one_philo_died == 0)
		{
			philosopher->rules->one_philo_died = 1;
			display_death(philosopher->rules, philosopher->id, "died");
		}
		pthread_mutex_unlock(&philosopher->rules->m_one_philo_died);
	}
}

void	*routine(t_philosopher *philosopher)
{	
	int beggin_sleeping;

	beggin_sleeping = 0;
	pthread_mutex_lock(&philosopher->rules->m_all_philo_created);
	pthread_mutex_unlock(&philosopher->rules->m_all_philo_created);

	while (!everyone_eated(philosopher) && !check_mutex(&philosopher->rules->m_one_philo_died, &philosopher->rules->one_philo_died))
	{
		if (no_death(philosopher))
			display_logs(philosopher->rules, philosopher->id, "is thinking");
		if (no_death(philosopher))
			eat(philosopher);
		// if (no_death(philosopher))
		{
			display_logs(philosopher->rules, philosopher->id, "is sleeping");
			beggin_sleeping = timestamp_in_ms(philosopher->rules);
			while (timestamp_in_ms(philosopher->rules) < (beggin_sleeping + philosopher->rules->time_to_sleep))
				usleep(philosopher->rules->time_to_sleep / 10);
			// usleep(philosopher->rules->time_to_sleep * 1000);
		}
	}
	return ((void*)philosopher);
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
