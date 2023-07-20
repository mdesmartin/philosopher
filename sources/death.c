/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:43:15 by mvogel            #+#    #+#             */
/*   Updated: 2023/07/20 13:43:32 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	check_mutex(pthread_mutex_t *mutex, int *mutex_value)
{
	int	res;

	res = 0;
	pthread_mutex_lock(mutex);
	if (*mutex_value > 0)
		res = 1;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	check_death(t_philosopher *philosopher)
{
	int	current_time;

	current_time = timestamp_in_ms(philosopher->rules);
	if (current_time - philosopher->last_meal_in_ms >= \
	philosopher->rules->time_to_die)
	{
		pthread_mutex_lock(&philosopher->rules->m_one_philo_died);
		if (philosopher->rules->one_philo_died == 0)
		{
			philosopher->rules->one_philo_died = philosopher->id;
			display_death(philosopher, "died");
		}
		pthread_mutex_unlock(&philosopher->rules->m_one_philo_died);
	}
}

int	no_death(t_philosopher *philosopher)
{
	check_death(philosopher);
	if (!check_mutex(&philosopher->rules->m_one_philo_died, \
	&philosopher->rules->one_philo_died))
		return (1);
	return (0);
}
