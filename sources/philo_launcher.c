/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/17 18:12:40 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

// logs
// 1 has taken a fork
// 2 is eating
// 3 is sleeping
// 4 is thinking
// 5 died

//fork only used to eat, so free to use when think and sleep
//when each time to eat reach or when one philo die, sim end
//each philo got a number betwen 1 and nb_philo

void	display_logs(int philo, char *log)
{
	printf("timestamp_in_ms %d %s", philo, log);
}

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

void	check_if_die(t_philosopher *philosopher)
{
	struct timeval	current_time;
	int current_ms;
	int	last_meal_ms;

	gettimeofday(&current_time, NULL);
	current_ms = (current_time.tv_sec * 1000) + current_time.tv_usec;
	last_meal_ms = (philosopher->last_meal.tv_sec * 1000) + philosopher->last_meal.tv_usec;
	if ((current_ms - last_meal_ms) >= philosopher->rules->time_to_die)
	{
		pthread_mutex_lock(&philosopher->rules->m_one_philo_died);
		philosopher->rules->one_philo_died = 1;
		pthread_mutex_unlock(&philosopher->rules->m_one_philo_died);
	}
}

void	*routine(t_philosopher *philosopher)
{	
	// wait untils all philo are created, mutex for that
	pthread_mutex_lock(&philosopher->rules->m_all_philo_created);
	pthread_mutex_unlock(&philosopher->rules->m_all_philo_created);

	while (!check_mutex(&philosopher->rules->m_one_philo_died, &philosopher->rules->one_philo_died) || !everyone_eated(philosopher))//notdead || tout le monde na pas mangé au moins x fois reste time to eat)// mutex qui change si un mort
	{
		//think
		display_logs(philosopher->id, "is thinking");
		//eat
		eat(philosopher);
		//sleep
		display_logs(philosopher->id, "is sleeping");
		usleep(philosopher->rules->time_to_sleep);//peut etre a convertir
		// si fin signaler a tout le monde quon est dead
		//quanmd tu meurt change une valeur que tout le monde peut voir, ils peuvent mourrir de faim pendant quil mangent
		check_if_die(philosopher);
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
		if (pthread_create(data->philosopher[i].thread, NULL, (void *)&routine, &data->philosopher[i]) != 0)
			return (1);
		if (pthread_mutex_init(data->philosopher[i].m_right_fork, NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_unlock(&data->rules.m_all_philo_created);
	return (0);
}
