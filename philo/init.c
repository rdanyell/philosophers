/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:54:42 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/16 15:56:23 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	pthread_mutex_t	*mutex;
	int				num_of_philo;

	num_of_philo = data->num_of_ph;
	mutex = malloc(sizeof(pthread_mutex_t) * num_of_philo);
	if (!mutex)
		return (ft_error("Malloc error"));
	while (num_of_philo--)
	{
		pthread_mutex_init(&mutex[num_of_philo], NULL);
	}
	data->forks = mutex;
	if (pthread_mutex_init(&data->main_mutex, NULL) != 0)
		return (ft_error("Mutex error"));
	return (0);
}

int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = malloc(sizeof(t_philo) * data->num_of_ph);
	if (!philos)
		return (ft_error("Malloc_error"));
	while (i++ < data->num_of_ph)
	{
		philos[i].id = i + 1;
		philos[i].times_ate = 0;
		philos[i].full = 0;
		philos[i].stop = 0;
		philos[i].num_of_ph = data->num_of_ph;
		philos[i].left = &data -> forks[i];
		if (i == 0)
			philos[i].right = &data -> forks[data->num_of_ph - 1];
		else
			philos[i].right = &data -> forks[i - 1];
		philos[i].start_time = ft_time();
		philos[i].last_ate_time = ft_time();
		philos[i].data = data;
	}
	data->philos = philos;
	return (0);
}

int	init_threads(t_data *data)
{
	int			num_of_philo;

	num_of_philo = data->num_of_ph;
	data->t_id = malloc(sizeof(pthread_t) * num_of_philo);
	while (num_of_philo--)
	{	
		pthread_create(&data->t_id[num_of_philo], NULL, ft_routine, \
			(void *)&data->philos[num_of_philo]);
		pthread_detach(data->t_id[num_of_philo]);
	}
	return (0);
}

int	init(t_data *data, int argc, char *argv[])
{
	data->num_of_ph = atoi_philo(argv[1]);
	data->d_time = atoi_philo(argv[2]);
	data->e_time = atoi_philo(argv[3]);
	data->s_time = atoi_philo(argv[4]);
	data->num_to_eat = -1;
	data->death = 0;
	if (argc == 6)
	{
		data->num_to_eat = atoi_philo(argv[5]);
		if (data->num_to_eat <= 0)
			return (ft_error("Arguments error"));
	}
	if (data->num_of_ph < 1 || data->d_time < 0 || data->e_time < 0
		|| data->s_time < 0)
		return (ft_error("Arguments error"));
	if (init_mutex(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}
