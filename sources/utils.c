/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:30:46 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/19 16:48:44 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	display_logs(t_philosopher *philosopher, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(philosopher->rules);
	pthread_mutex_lock(&philosopher->rules->m_printf);
	if (no_death(philosopher))
		printf("%06d %d %s\n", timestamp, philosopher->id, log);
	pthread_mutex_unlock(&philosopher->rules->m_printf);
}

void	display_death(t_philosopher *philosopher, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(philosopher->rules);
	pthread_mutex_lock(&philosopher->rules->m_printf);
	printf("%06d %d %s\n", timestamp, philosopher->id, log);
	pthread_mutex_unlock(&philosopher->rules->m_printf);
}

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
	// if (current_time == 0)
	// 	return ; 
	if (current_time - philosopher->last_meal_in_ms >= philosopher->rules->time_to_die)
	{
		pthread_mutex_lock(&philosopher->rules->m_one_philo_died);
		if (philosopher->rules->one_philo_died == 0)
		{
			philosopher->rules->one_philo_died = philosopher->id;
			// printf("ded\n");
			display_death(philosopher, "died");
		}
		pthread_mutex_unlock(&philosopher->rules->m_one_philo_died);
		// exit(0);
	}
}

int	no_death(t_philosopher *philosopher)
{
	check_death(philosopher);
	if (!check_mutex(&philosopher->rules->m_one_philo_died, &philosopher->rules->one_philo_died))
		return (1);
	return (0);
}