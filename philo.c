/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kas <kas@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/05 11:41:20 by kas           #+#    #+#                 */
/*   Updated: 2021/09/21 14:08:48 by kde-rooi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	printf("%s\n", str);
	return (EXIT_FAILURE);
}

int	input_error(int argc, char **argv)
{
	int	i;

	i = 3;
	if (argc < 5 || argc > 6)
		return (error("No or wrong philosophers input"));
	if (ft_atoi(argv[1]) <= 0)
		return (error("No or wrong philosophers input"));
	if (ft_atoi(argv[2]) <= 0)
		return (error("No or wrong time to die input"));
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (error("No or wrong eat/sleep/timeseaten input"));
		i++;
	}
	return (EXIT_SUCCES);
}

int	start_threading(t_meta data)
{
	int	i;

	i = 0;
	while (i < data.n_philo)
	{
		if (philo_init(&data, i))
			return (EXIT_FAILURE);
		if (pthread_create(&data.philo[i].thread, NULL,
				&life_cycle, &data.philo[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_create(&data.status_check, NULL, &check_status, &data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCES);
}

int	join_threads(t_meta data)
{
	int	i;

	i = 0;
	while (i < data.n_philo)
	{
		if (pthread_join(data.philo[i].thread, NULL))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_join(data.status_check, NULL))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data.n_philo)
	{
		pthread_mutex_destroy(&data.fork[i]);
		i++;
	}
	return (EXIT_SUCCES);
}

int	main(int argc, char **argv)
{
	t_meta		data;

	if (input_error(argc, argv))
		return (EXIT_FAILURE);
	if (meta_init(&data, argc, argv))
		return (EXIT_FAILURE);
	if (start_threading(data))
		return (EXIT_FAILURE);
	if (join_threads(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCES);
}
