/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:50:26 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/26 11:59:20 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_action(t_data *data)
{
	data->last_eat_t = ft_time();
	pthread_create(&data->pthread_id, NULL, &monitor, data);
	pthread_detach(data->pthread_id);
	while (1)
	{
		sem_wait(data->semfork);
		my_print(data, "has taken a fork");
		sem_wait(data->semfork);
		my_print(data, "has taken a fork");
		my_print(data, "is eating");
		sem_wait(data->sem_check);
		data->last_eat_t = ft_time();
		sem_post(data->sem_check);
		my_sleep(data->e_time);
		sem_wait(data->sem_check);
		data-> times_ate += 1;
		if (data->times_ate == data->num_to_eat)
			sem_post(data->sem_eat);
		sem_post(data->sem_check);
		sem_post(data->semfork);
		sem_post(data->semfork);
		my_print(data, "is sleeping");
		my_sleep(data->s_time);
		my_print(data, "is thinking");
	}
}

void	*check_eat(void *args)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)args;
	sem_wait(data->sem_main);
	while (i < data->num_of_ph)
	{
		sem_post(data->sem_main);
		sem_wait(data->sem_eat);
		sem_wait(data->sem_main);
		i++;
	}
	sem_post(data->sem_die);
	return (NULL);
}

int	control(t_data *data)
{
	int	i;

	i = 0;
	if (data->e_time > 0)
	{
		if (pthread_create(&data->parent_id, NULL, &check_eat, data) != 0)
			return (ft_error ("Thread error"));
		if (pthread_detach(data->parent_id) != 0)
			return (ft_error ("Thread error"));
	}
	sem_wait(data->sem_die);
	while (i < data->num_of_ph)
	{
		kill (data->pid_philo[i], SIGKILL);
		i++;
	}
	return (0);
}

void	finish(t_data *data)
{
	sem_post(data->sem_eat);
	sem_close(data->sem_eat);
	sem_close(data->semfork);
	sem_post(data->sem_main);
	sem_close(data->sem_main);
	sem_close(data->sem_die);
	sem_unlink("/semfork");
	sem_unlink("/sem_main");
	sem_unlink("/sem_die");
	sem_unlink("/sem_eat");
	if (data->pid_philo)
		free(data->pid_philo);
	if (data)
		free(data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of arguments"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Malloc error"));
	if (init(data, argc, argv))
		return (1);
	if (start_philo(data))
		return (ft_error("Couldn't create philo"));
	if (control(data))
		return (1);
	finish(data);
	return (0);
}
