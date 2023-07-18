/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:00:19 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 17:29:45 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	timestamp_in_ms(t_rules *rules)
{
	struct timeval	current_time;
	struct timeval	timestamp;
	int				timestamp_in_ms;

	gettimeofday(&current_time, NULL);
	timestamp.tv_sec = current_time.tv_sec - rules->begin_time.tv_sec;
	timestamp.tv_usec = current_time.tv_usec - rules->begin_time.tv_usec;
	timestamp_in_ms = (timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000);
	return (timestamp_in_ms);
}

