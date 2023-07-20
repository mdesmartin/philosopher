/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:20:50 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/20 13:21:22 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

/********************************  structrures  *******************************/

typedef struct s_rules
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_time;
	pthread_mutex_t	m_all_philo_created;
	pthread_mutex_t	m_one_philo_died;
	int				one_philo_died;
	struct timeval	begin_time;
	pthread_mutex_t	m_printf;
}					t_rules;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	m_left_fork;
	int				left_fork;
	pthread_mutex_t	*m_right_fork;
	int				*right_fork;
	int				nb_of_meals;
	int				last_meal_in_ms;
	int				last_sleep_in_ms;
	t_rules			*rules;
}					t_philosopher;

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
void	eat(t_philosopher *philosopher);
int		check_mutex(pthread_mutex_t *mutex, int *mutex_value);
int		timestamp_in_ms(t_rules *rules);
void	check_death(t_philosopher *philosopher);
int		everyone_eated(t_philosopher *philosopher);

/***********************************  UTILS  **********************************/

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	display_logs(t_philosopher *philosopher, char *log);
int		no_death(t_philosopher *philosopher);
void	*free_tab(t_philosopher *tab);
void	p_pause(t_philosopher *philosopher, int last_action, int time_action);

#endif