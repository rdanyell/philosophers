/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:19:05 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/16 15:55:47 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	last_forks(t_philo *philo)
{
	my_sleep(5);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->data->main_mutex);
	printf("%lu %d has taken a fork\n", ft_time() - philo->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->main_mutex);
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&philo->data->main_mutex);
	printf("%lu %d has taken a fork\n", ft_time() - philo->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->data->main_mutex);
}

void	taking_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id == philo->data->num_of_ph)
		last_forks(philo);
	else
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(&data->main_mutex);
		printf("%lu %d has taken a fork\n", ft_time() - philo->start_time, \
			philo->id);
		pthread_mutex_unlock(&data->main_mutex);
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(&data->main_mutex);
		printf("%lu %d has taken a fork\n", ft_time() - philo->start_time, \
			philo->id);
		pthread_mutex_unlock(&data->main_mutex);
	}
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->main_mutex);
	printf("%lu %d is eating\n", ft_time() - philo->start_time, philo->id);
	philo->last_ate_time = ft_time();
	pthread_mutex_unlock(&data->main_mutex);
	my_sleep(data->e_time);
	pthread_mutex_lock(&data->main_mutex);
	philo->times_ate += 1;
	if (philo->times_ate >= philo->data->num_to_eat && \
		philo->data->num_to_eat > 0)
		philo->full = 1;
	pthread_mutex_unlock(&data->main_mutex);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->main_mutex);
	printf("%lu %d is sleeping\n", ft_time() - philo->start_time, \
			philo->id);
	pthread_mutex_unlock(&data->main_mutex);
	my_sleep(data->s_time);
}

void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->main_mutex);
	printf("%lu %d is thinking\n", ft_time() - philo->start_time, \
		philo->id);
	pthread_mutex_unlock(&data->main_mutex);
}
