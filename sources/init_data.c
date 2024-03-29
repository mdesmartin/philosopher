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

int	init_rules(t_data *data, char **argv)
{
	t_rules	rules;

	rules.nb_of_philo = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules.must_eat_time = ft_atoi(argv[5]);
	else
		rules.must_eat_time = 0;
	if (pthread_mutex_init(&rules.m_all_philo_created, NULL) != 0)
		return (display_error("In initializing m_all_philo_created\n"), 1);
	if (pthread_mutex_init(&rules.m_one_philo_died, NULL) != 0)
		return (display_error("In initializing m_one_philo_died\n"), 1);
	if (pthread_mutex_init(&rules.m_printf, NULL) != 0)
		return (display_error("In initializing m_printf\n"), 1);
	rules.one_philo_died = 0;
	data->rules = rules;
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	if (init_rules(data, argv))
		return (1);
	if (init_philosophers(data, data->rules))
		return (1);
	return (0);
}
