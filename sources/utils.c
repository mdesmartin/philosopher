/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:30:46 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 16:02:51 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	display_logs(t_rules *rules, int philo_id, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(rules);
	printf("%d %d %s\n", timestamp, philo_id, log);
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