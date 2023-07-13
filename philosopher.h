/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:20:50 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/11 14:04:18 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//a supprimer
#include <stdio.h>

/********************************  structrures  *******************************/


typedef struct s_rules
{
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_eat;
}				t_rules;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t m_left_fork;//unlock
	int				left_fork;
	pthread_mutex_t *m_right_fork;
	int 			*right_fork;//pointeur vers la fourchette du voisin de droite
	t_rules			*rules;
}				t_philosopher;

typedef struct s_data
{
	t_rules			rules;
	t_philosopher	*philosopher;
}				t_data;

/***********************************  -----  **********************************/

int		init_data(t_data *data, char **argv);
int		init_philosophers(t_data *data, t_rules rules);
int		check_arg(int argc, char **argv);
int		philo_launcher(t_data *data);

/***********************************  UTILS  **********************************/

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

#endif