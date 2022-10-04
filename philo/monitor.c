/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:24:10 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/16 15:54:42 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_death(t_philo *philo, int i)
{
	long	curr_time;
	long	life_time;

	pthread_mutex_lock(&philo->data->main_mutex);
	curr_time = ft_time() - philo->start_time;
	life_time = ft_time() - philo[i].last_ate_time;
	if (life_time > philo[i].data->d_time)
	{
		philo->data->death = 1;
		printf("%ld %d died\n", curr_time, philo[i].id);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->main_mutex);
	return (0);
}

int	count_meals(t_philo *philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	pthread_mutex_lock(&philos->data->main_mutex);
	while (i < philos->num_of_ph)
	{
		if (philos[i].full)
			full++;
		i++;
	}
	if (full == philos->num_of_ph)
		return (1);
	pthread_mutex_unlock(&philos->data->main_mutex);
	return (0);
}

int	ft_monitor(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = 0;
	while (1)
	{
		while (i < data->num_of_ph)
		{
			if (philo_death(philos, i) == 1)
				return (1);
			if (data->num_to_eat != -1)
			{
				if (count_meals(philos))
					return (0);
			}
			i++;
		}
		i = 0;
		my_sleep(5);
	}
	return (0);
}

void	*ft_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2 == 0)
		my_sleep(5);
	while (1)
	{	
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
