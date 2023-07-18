/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:28:48 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/17 17:23:08 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int take_fork(pthread_mutex_t *mutex, int *fork, int philo_id)
{
	while (*fork == 0)//1?
	{
		pthread_mutex_lock(mutex);
		if (*fork = 1)
		{
			*fork = 0;
			display_log(philo_id, "has taken a fork");
			pthread_mutex_unlock(mutex);
			return (1);
		}
		pthread_mutex_unlock(mutex);
	}
	return (0);
}

void give_back_fork(pthread_mutex_t *mutex, int *fork)
{
	pthread_mutex_lock(mutex);
	*fork = 1;
	pthread_mutex_unlock(mutex);
}

void	eat(t_philosopher *philosopher)
{
	if (take_fork(&philosopher->m_left_fork, philosopher->left_fork, philosopher->id) &&
	take_fork(philosopher->m_right_fork, philosopher->left_fork, philosopher->id))
	{
		display_log(philosopher->id, "is eating");
		gettimeofday(&philosopher->last_meal, NULL);
		usleep(philosopher->rules->time_to_eat);//peut etre a convertir
		give_back_fork(&philosopher->m_left_fork, philosopher->left_fork);
		give_back_fork(philosopher->m_right_fork, philosopher->right_fork);
		philosopher->nb_of_meals += 1;// add time of eat
	}
}