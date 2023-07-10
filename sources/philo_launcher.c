/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:39:44 by mdesmart          #+#    #+#             */
/*   Updated: 2023/06/28 15:30:29 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

// logs
// 1 has taken a fork
// 2 is eating
// 3 is sleeping
// 4 is thinking
// 5 died

void	display_logs(int philo, char *log)
{
	ft_printf("timestamp_in_ms %d %s", philo, log);
}

void	*routine()
{
	// wait untils all philo are created, mutex for that
	// tant que tous les philos sont en vie faire la routine sinon stop, clean and free tout
	display_log(philo, "is thinking");
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

int	philo_launcher(t_data process, t_thread *philosophers)
{
	//malloc nb_philo structure dans un tableau, chaque structure contenant un pthread et autres donnéees propre au philo
	//  pthread _mutex_init(&mutex, NULL) where to init multiple of this ?


	/// je fait quoi du dernier thread ? je le met a null ou sert a rien et je supprinme ?
	// int nb_philo;

	// nb_philo = process->number_of_philosophers;

	int	i;

	i = 0;
	while (philosophers[i])
	{
		if (pthread_create(&philosophers[i], NULL, &routine, NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(philosophers[i]->fork, NULL) != 0)
			return (NULL);
		i++;
	}
}
