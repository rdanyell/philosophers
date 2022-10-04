/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:54:42 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/26 11:58:36 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_time();
	while (i < data->num_of_ph)
	{
		data->ph_index = i + 1;
		data->pid_philo[i] = fork();
		if (data->pid_philo[i] == 0)
			philo_action(data);
		i++;
	}
	return (0);
}

int	ft_inint_sem(t_data *data)
{
	sem_unlink("/semfork");
	sem_unlink("/sem_main");
	sem_unlink("/sem_die");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_check");
	data->semfork = sem_open("/semfork", O_CREAT, 0777, data->num_of_ph);
	data->sem_main = sem_open("/sem_main", O_CREAT, 0777, 1);
	data->sem_die = sem_open("/sem_die", O_CREAT, 0777, 0);
	data->sem_eat = sem_open("/sem_eat", O_CREAT, 0777, 0);
	data->sem_check = sem_open("/sem_check", O_CREAT, 0777, 1);
	return (0);
}

int	init(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(t_data));
	data->num_of_ph = atoi_philo(argv[1]);
	data->d_time = atoi_philo(argv[2]);
	data->e_time = atoi_philo(argv[3]);
	data->s_time = atoi_philo(argv[4]);
	data->num_to_eat = -1;
	if (argc == 6)
	{
		data->num_to_eat = atoi_philo(argv[5]);
		if (data->num_to_eat <= 0)
			return (ft_error("Arguments error"));
	}
	if (data->num_of_ph < 1 || data->d_time < 0 || data->e_time < 0
		|| data->s_time < 0)
		return (ft_error("Arguments error"));
	data->pid_philo = malloc(sizeof(int) * data->num_of_ph);
	if (!data->pid_philo)
		return (ft_error("Malloc error"));
	memset(data->pid_philo, 0, sizeof(pid_t) * data->num_of_ph);
	ft_inint_sem(data);
	return (0);
}

void	*monitor(void *args)
{
	time_t	now;
	time_t	time_diff;
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		now = ft_time();
		sem_wait(data->sem_check);
		time_diff = now - data->last_eat_t;
		sem_post(data->sem_check);
		if (time_diff > data->d_time)
		{
			sem_wait(data->sem_main);
			now = ft_time() - data->start;
			printf("%ld %d died\n", now, data->ph_index);
			sem_post(data->sem_die);
			return (0);
		}
	}
	return (NULL);
}
