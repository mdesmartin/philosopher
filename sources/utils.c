/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:30:46 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 18:23:11 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	display_logs(t_rules *rules, int philo_id, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(rules);
	if (!check_mutex(&rules->m_one_philo_died, &rules->one_philo_died))
		printf("%06d %d %s\n", timestamp, philo_id, log);
}

void	display_death(t_rules *rules, int philo_id, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(rules);
	printf("%06d %d %s\n", timestamp, philo_id, log);
}

int	check_mutex(pthread_mutex_t *mutex, int *mutex_value)
{
	int	res;

	res = 0;
	pthread_mutex_lock(mutex);
	if (*mutex_value == 1)
		res = 1;
	pthread_mutex_unlock(mutex);
	return (res);
}

// int	no_death(t_philosopher *philosopher)
// {
// 	check_death(philosopher);
// 	if (!check_mutex(&philosopher->rules->m_one_philo_died, &philosopher->rules->one_philo_died))
// 		return (1);
// 	return (0);
// }