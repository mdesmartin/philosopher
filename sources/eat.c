/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:28:48 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/19 13:09:57 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int take_fork(pthread_mutex_t *mutex, int *fork, t_philosopher *philosopher)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (*fork == 1)
		{
			*fork = 0;
			display_logs(philosopher->rules, philosopher->id, "has taken a fork");
			pthread_mutex_unlock(mutex);
			return (1);
		}
		else
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
	if (take_fork(&philosopher->m_left_fork, &philosopher->left_fork, philosopher) &&
	take_fork(philosopher->m_right_fork, philosopher->right_fork, philosopher))
	{
		display_logs(philosopher->rules, philosopher->id, "is eating");
		philosopher->last_meal_in_ms = timestamp_in_ms(philosopher->rules);
		while (timestamp_in_ms(philosopher->rules) < (philosopher->last_meal_in_ms + philosopher->rules->time_to_eat))
			usleep(philosopher->rules->time_to_eat / 4);
		give_back_fork(&philosopher->m_left_fork, &philosopher->left_fork);
		give_back_fork(philosopher->m_right_fork, philosopher->right_fork);
		philosopher->nb_of_meals += 1;
	}
}