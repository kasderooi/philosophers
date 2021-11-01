/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-rooi <kde-rooi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/20 14:05:51 by kde-rooi      #+#    #+#                 */
/*   Updated: 2021/09/21 14:36:57 by kde-rooi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	talk(char *str, t_philo *philo)
{
	int				t_current;

	if (philo->data->status != ALIVE)
		return (EXIT_FAILURE);
	t_current = make_time();
	if (philo->status == EATING)
		philo->t_lasteat = t_current;
	printf("%d\t%d\t%s\n", t_current - philo->data->t_start,
		philo->philo + 1, str);
	return (EXIT_SUCCES);
}

int	check_death(t_meta *data, int i)
{
	pthread_mutex_lock(&data->write);
	pthread_mutex_lock(&data->shrodinger);
	if (data->philo[i].status != EATING)
	{
		if ((make_time() - data->philo[i].t_lasteat) > data->t_die)
		{
			data->status = DEAD;
			// while (data->n_philo >= 0)
			// {
			// 	data->philo[data->n_philo].status = DEAD;
			// 	data->n_philo--;
			// }
			talk(" died", &data->philo[i]);
			pthread_mutex_unlock(&data->shrodinger);
			pthread_mutex_unlock(&data->write);
			return (DEAD);
		}
		if (data->philo[i].times_eaten == data->time_to_eat)
		{
			data->status = DEAD;
			pthread_mutex_unlock(&data->shrodinger);
			pthread_mutex_unlock(&data->write);
			return (DEAD);
		}
	}
	pthread_mutex_unlock(&data->shrodinger);
	pthread_mutex_unlock(&data->write);
	return (ALIVE);
}
