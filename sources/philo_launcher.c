/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 16:09:02 by mdesmart         ###   ########lyon.fr   */
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
	if (timestamp_in_ms(philosopher->rules) - philosopher->last_meal_in_ms >= philosopher->rules->time_to_die)
	{
		pthread_mutex_lock(&philosopher->rules->m_one_philo_died);
		philosopher->rules->one_philo_died = 1;
		display_logs(philosopher->rules, philosopher->id, "died");
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
		display_logs(philosopher->rules, philosopher->id, "is thinking");
		//eat
		eat(philosopher);
		//sleep
		display_logs(philosopher->rules, philosopher->id, "is sleeping");
		usleep(philosopher->rules->time_to_sleep * 1000);//peut etre a convertir
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
}//faut mettre un join ici pour attendre que les tread se termine puis ensuite end of game
