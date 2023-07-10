/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:16:33 by mdesmart          #+#    #+#             */
/*   Updated: 2023/06/28 14:28:19 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	init_structures(t_data *process, t_thread *philosophers, char **argv)
{
	init_data(process, argv);
	init_philosophers(philosophers, *process);
}

void init_data(t_data *process, char **argv)
{
	process->nb_of_philo = ft_atoi(argv[1]);
	process->time_to_die = ft_atoi(argv[2]);
	process->time_to_eat = ft_atoi(argv[3]);
	process->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		process->number_of_eat = ft_atoi(argv[5]);
	else
		process->number_of_eat = -1;
}

void	init_philosophers(t_thread *philosophers, t_data process)
{
	philosophers = malloc(sizeof(t_thread) * (process.nb_of_philo + 1));
	if (!philosophers)
		return (NULL);
}
