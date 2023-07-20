/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:28:48 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/20 13:23:20 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

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

void	give_back_fork(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->m_left_fork);
	philosopher->left_fork = 1;
	pthread_mutex_unlock(&philosopher->m_left_fork);
	pthread_mutex_lock(philosopher->m_right_fork);
	*philosopher->right_fork = 1;
	pthread_mutex_unlock(philosopher->m_right_fork);
}

void	fork_taken(t_philosopher *philosopher, int *fork, int *took)
{
	*fork = 0;
	display_logs(philosopher, "has taken a fork");
	*took = 1;
}

int	take_forks(t_philosopher *philosopher)
{
	int	took[2];

	took[0] = 0;
	took[1] = 0;
	while (no_death(philosopher) && (!took[0] || !took[1]))
	{
		if (took[0] == 0)
		{
			pthread_mutex_lock(&philosopher->m_left_fork);
			if (philosopher->left_fork == 1)
				fork_taken(philosopher, &philosopher->left_fork, &took[0]);
			pthread_mutex_unlock(&philosopher->m_left_fork);
		}
		if (took[1] == 0)
		{
			pthread_mutex_lock(philosopher->m_right_fork);
			if (*philosopher->right_fork == 1)
				fork_taken(philosopher, philosopher->right_fork, &took[1]);
			pthread_mutex_unlock(philosopher->m_right_fork);
		}
		// if (!took[0] || !took[1])
		// usleep(400);
	}
	return (1);
}

void	eat(t_philosopher *philosopher)
{
	if (take_forks(philosopher))
	{
		display_logs(philosopher, "is eating");
		philosopher->last_meal_in_ms = timestamp_in_ms(philosopher->rules);
		p_pause(philosopher, philosopher->last_meal_in_ms, \
		philosopher->rules->time_to_eat);
		give_back_fork(philosopher);
		philosopher->nb_of_meals += 1;
	}
}
