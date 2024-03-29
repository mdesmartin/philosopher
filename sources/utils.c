/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:27:17 by mvogel            #+#    #+#             */
/*   Updated: 2023/07/21 10:34:46 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res != ((res * 10) + ((str[i] - 48) * sign)) / 10)
			return ((sign + 1) / 2 / -1);
		res = res * 10 + ((str[i] - 48) * sign);
		i++;
	}
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	free_n_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_of_philo)
	{
		pthread_mutex_destroy(&data->philosopher[i].m_left_fork);
		i++;
	}
	pthread_mutex_destroy(&data->rules.m_one_philo_died);
	pthread_mutex_destroy(&data->rules.m_all_philo_created);
	if (data->philosopher)
		free(data->philosopher);
}
