/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:28:48 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 16:29:10 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int take_fork(pthread_mutex_t *mutex, int *fork, t_philosopher *philosopher)
{
	// printf("fork1\n");
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (*fork == 1)
		{
			// printf("fork2\n");
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
	// printf("eat1\n");
	if (take_fork(&philosopher->m_left_fork, &philosopher->left_fork, philosopher) &&
	take_fork(philosopher->m_right_fork, philosopher->right_fork, philosopher))
	{
		printf("eat2\n");
		display_logs(philosopher->rules, philosopher->id, "is eating");
		usleep(philosopher->rules->time_to_eat * 1000);
		give_back_fork(&philosopher->m_left_fork, &philosopher->left_fork);
		give_back_fork(philosopher->m_right_fork, philosopher->right_fork);
		philosopher->nb_of_meals += 1;
	}
}