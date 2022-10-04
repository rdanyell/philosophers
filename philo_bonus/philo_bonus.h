/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:50:34 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/23 17:12:04 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <errno.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	int			num_of_ph;
	int			d_time;
	int			e_time;
	int			s_time;
	int			num_to_eat;
	int			ph_index;
	int			times_ate;
	sem_t		*semfork;
	sem_t		*sem_main;
	sem_t		*sem_die;
	sem_t		*sem_eat;
	sem_t		*sem_check;
	pid_t		*pid_philo;
	time_t		start;
	time_t		last_eat_t;
	pthread_t	pthread_id;
	pthread_t	parent_id;
}				t_data;

int		ft_error(char *str);
int		init(t_data *data, int argc, char *argv[]);
int		start_philo(t_data *data);
void	philo_action(t_data *data);
void	*monitor(void *args);

int		atoi_philo(const char *str);
long	ft_time(void);
void	my_sleep(int ms);
void	my_print(t_data *data, char *str);

#endif