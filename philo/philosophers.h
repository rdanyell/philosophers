/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:50:34 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/16 15:56:16 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <errno.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				times_ate;
	int				full;
	int				stop;
	int				num_of_ph;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	time_t			start_time;
	time_t			last_ate_time;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_of_ph;
	int				d_time;
	int				e_time;
	int				s_time;
	int				num_to_eat;
	int				death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	main_mutex;
	pthread_t		*t_id;
	t_philo			*philos;
	time_t			start_time;
}					t_data;

int		ft_error(char *str);
int		init(t_data *data, int argc, char *argv[]);
int		init_mutex(t_data *data);
int		init_threads(t_data *data);
void	end_threads(t_data *data);
void	*ft_routine(void *philos);
void	philo_full(t_philo *philo);
int		philo_death(t_philo *philo, int i);
int		ft_monitor(t_data *data);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	taking_forks(t_philo *philo);
void	thinking(t_philo *philo);

int		atoi_philo(const char *str);
long	ft_time(void);
void	my_sleep(int ms);

#endif