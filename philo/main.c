/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:50:26 by rdanyell          #+#    #+#             */
/*   Updated: 2022/05/26 12:53:30 by rdanyell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

void	finish_mutex(t_data *data)
{
	int	nbr;

	nbr = data->num_of_ph;
	while (nbr--)
	{
		pthread_mutex_unlock(&data->forks[nbr]);
		pthread_mutex_destroy(&data->forks[nbr]);
	}
	pthread_mutex_destroy(&data->main_mutex);
	free(data->t_id);
	free(data->philos);
	free(data->forks);
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
	if (init_threads(data))
		return (1);
	ft_monitor(data);
	finish_mutex(data);
	return (0);
}
