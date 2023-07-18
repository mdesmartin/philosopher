/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:57:47 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/17 18:17:28 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	give_id(t_philosopher *philosopher, int nb_of_philo)
{
	int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		philosopher[i].id = i + 1;
		i++;
	}
}

void	give_right_fork(t_philosopher *philosopher, int nb_of_philo)
{
	int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		philosopher[i].left_fork = 0;
		pthread_mutex_init(&philosopher[i].m_left_fork, NULL);
		// pthread_mutex_lock(&philosopher[i].m_left_fork);
		i++;
	}
}

void	give_left_fork(t_philosopher *philosopher, int nb_of_philo)
{
	int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (i == 0)
		{
			philosopher[i].right_fork = philosopher[nb_of_philo].right_fork;
			philosopher[i].m_right_fork = philosopher[nb_of_philo].m_right_fork;
		}
		else
		{
			philosopher[i].right_fork = philosopher[i - 1].right_fork;
			philosopher[i].m_right_fork = philosopher[i - 1].m_right_fork;
		}
		i++;
	}
}

void	give_rules(t_data *data, t_philosopher *philosopher, int nb_of_philo)
{
	int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		philosopher[i].rules = &data->rules;
		i++;
	}
} 

//cree un tab de philo
int	init_philosophers(t_data *data, t_rules rules)
{
	t_philosopher *philosopher;

	philosopher = malloc(sizeof(philosopher) * (rules.nb_of_philo));
	if (!philosopher)
		return (1);
	give_id(philosopher, rules.nb_of_philo);
	give_left_fork(philosopher, rules.nb_of_philo);
	give_right_fork(philosopher, rules.nb_of_philo);
	give_rules(data, philosopher, rules.nb_of_philo);
	data->philosopher = philosopher;
	return (0);
}
