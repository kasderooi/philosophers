/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kas <kas@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/05 13:27:47 by kas           #+#    #+#                 */
/*   Updated: 2021/09/21 14:27:14 by kde-rooi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define DEAD 0
# define ALIVE 1
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define EXIT_FAILURE 1
# define EXIT_SUCCES 0
# define RIGHT 0
# define LEFT 1

typedef struct s_philo
{
	int				total;
	int				philo;
	int				t_lasteat;
	int				status;
	int				times_eaten;
	pthread_mutex_t	*fork[2];
	pthread_t		thread;
	struct s_meta	*data;
}					t_philo;

typedef struct s_meta
{
	int				n_philo;
	int				t_start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				time_to_eat;
	int				status;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
	pthread_mutex_t	shrodinger;
	pthread_t		status_check;
	t_philo			*philo;
}					t_meta;

size_t			ft_strlen(char *str);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_isdigit(char c);

void			*life_cycle(void *philosopher);
void			*check_status(void *data_set);

int				make_time(void);
int				talk(char *str, t_philo *philo);
int				check_death(t_meta *data, int i);

int				meta_init(t_meta *data, int argc, char **argv);
int				philo_init(t_meta *data, int i);

#endif
