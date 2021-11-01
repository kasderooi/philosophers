/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-rooi <kde-rooi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/21 09:51:03 by kde-rooi      #+#    #+#                 */
/*   Updated: 2021/09/21 14:27:11 by kde-rooi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meta_init(t_meta *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->status = ALIVE;
	data->t_start = make_time();
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->time_to_eat = ft_atoi(argv[5]);
	data->fork = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		return (EXIT_FAILURE);
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->write, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->shrodinger, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCES);
}

int	philo_init(t_meta *data, int i)
{
	if (pthread_mutex_init(&data->fork[i], NULL))
		return (EXIT_FAILURE);
	data->philo[i].total = data->n_philo;
	data->philo[i].philo = i;
	data->philo[i].data = data;
	data->philo[i].t_lasteat = make_time();
	data->philo[i].status = THINKING;
	data->philo[i].fork[RIGHT] = &data->fork[i];
	if (i == 0)
		data->philo[i].fork[LEFT] = &data->fork[data->n_philo - 1];
	else
		data->philo[i].fork[LEFT] = &data->fork[i - 1];
	data->philo[i].times_eaten = 0;
	return (EXIT_SUCCES);
}
