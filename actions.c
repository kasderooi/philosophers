/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-rooi <kde-rooi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 13:59:55 by kde-rooi      #+#    #+#                 */
/*   Updated: 2021/09/21 14:40:44 by kde-rooi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_fork(t_philo *philo, int orientation)
{
	pthread_mutex_lock(&philo->data->shrodinger);
	pthread_mutex_unlock(&philo->data->shrodinger);
	if (philo->status == DEAD)
	{
		if (orientation == LEFT)
			pthread_mutex_unlock(philo->fork[RIGHT]);
		return (1);
	}
	pthread_mutex_lock(philo->fork[orientation]);
	pthread_mutex_lock(&philo->data->write);
	talk(" has taken a fork", philo);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

static void	eating(t_philo *philo)
{
	if (philo->philo % 2 == 1)
		usleep(100);
	if (handle_fork(philo, RIGHT))
		return ;
	if (philo->fork[LEFT] == philo->fork[RIGHT])
		usleep(philo->data->t_die * 1000 + 900);
	if (handle_fork(philo, LEFT))
		return ;
	pthread_mutex_lock(&philo->data->write);
	if (philo->status == DEAD)
	{
		pthread_mutex_unlock(philo->fork[RIGHT]);
		pthread_mutex_unlock(philo->fork[LEFT]);
		return ;
	}
	pthread_mutex_lock(&philo->data->shrodinger);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->data->shrodinger);
	talk(" is eating", philo);
	pthread_mutex_unlock(&philo->data->write);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	pthread_mutex_unlock(philo->fork[LEFT]);
	philo->times_eaten++;
	philo->status = SLEEPING;
}

static void	sleeping(t_philo *philo)
{
	int	check;

	// if (philo->data->status != ALIVE)
	// 	return ;
	pthread_mutex_lock(&philo->data->write);
	check = talk(" is sleeping", philo);
	pthread_mutex_unlock(&philo->data->write);
	if (check)
		return ;
	usleep(philo->data->t_sleep * 1000);
}

void	*life_cycle(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	while (philo->data->status == ALIVE)
	{
		eating(philo);
		sleeping(philo);
		// if (philo->data->status == DEAD)
		// 	return (NULL);
		pthread_mutex_lock(&philo->data->write);
		talk(" is thinking", philo);
		pthread_mutex_unlock(&philo->data->write);
	}
	return (NULL);
}

void	*check_status(void *data_set)
{
	t_meta			*data;
	int				i;

	data = data_set;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (check_death(data, i) == DEAD)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
