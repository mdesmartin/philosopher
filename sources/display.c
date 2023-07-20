/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:30:46 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/20 13:47:22 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	display_error(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

void	display_logs(t_philosopher *philosopher, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(philosopher->rules);
	pthread_mutex_lock(&philosopher->rules->m_printf);
	if (no_death(philosopher))
		printf("%06d %d %s\n", timestamp, philosopher->id, log);
	pthread_mutex_unlock(&philosopher->rules->m_printf);
}

void	display_death(t_philosopher *philosopher, char *log)
{
	int	timestamp;

	timestamp = timestamp_in_ms(philosopher->rules);
	pthread_mutex_lock(&philosopher->rules->m_printf);
	printf("%06d %d %s\n", timestamp, philosopher->id, log);
	pthread_mutex_unlock(&philosopher->rules->m_printf);
}
