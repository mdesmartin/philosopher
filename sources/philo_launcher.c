/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/12 17:22:07 by mdesmart         ###   ########lyon.fr   */
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

void	*routine()
{
	// wait untils all philo are created, mutex for that
	// tant que tous les philos sont en vie faire la routine sinon stop, clean and free tout, pour savoir si en vie wait une valeur de retour ?
	display_logs(philo, "is thinking");
	if (time to die has come)
		display_log(philo, "died");
	if (pthread_mutex_lock(&fork[philo - 1]) && pthread_mutex_lock(&philo + 1))// 2 fork / how to check mutex ? pour le dernier regarder a droite la fourchette 0
	{
		pthread_mutex_lock(&mutex)
		display_log(philo, "has taken a fork");
		eat display_log(philo, "is eating");
		pthread_mutex_unlock(&mutex)
	}
	sleep display_log(philo, "is sleeping")
}

int	philo_launcher(t_data *data)
{
	//malloc nb_philo structure dans un tableau, chaque structure contenant un pthread et autres donnéees propre au philo
	//  pthread _mutex_init(&mutex, NULL) where to init multiple of this ?


	int	i;

	i = 0;
	while (i < data->rules.nb_of_philo)
	{
		if (pthread_create(data->philosopher[i].thread, NULL, &routine, NULL) != 0)
			return (1);
		if (pthread_mutex_init(data->philosopher[i].m_right_fork, NULL) != 0)
			return (1);
		i++;
	}
	if 
}
