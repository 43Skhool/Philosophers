/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:01:24 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/16 12:49:35 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include "utils.h"

// Is managed as a "chain" connecting first and last "nodes"
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	size_t			birthday;

	struct s_philo	*right_philo;
	struct s_philo	*left_philo;

	struct s_data	*data;

	pthread_t		thread_id;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

// All usigned because they can't be negative
//Game over is used to tell to all philos when someone is death so all thread will stop
//Timestamp: time when the program is started
typedef struct s_data
{
	int				number_of_philosophers;	
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_count;

	t_bool			game_over;
	size_t			timestamp;
	t_philo			*first_philo;
	pthread_mutex_t write_lock;
	pthread_mutex_t game_lock;
	pthread_mutex_t p_mutex;
}	t_data;

t_data	*parse_arguments(int argc, char *argv[]);

t_data	*initialize_table(t_data *data);

void	display_table(t_data *data);

void	free_and_exit(t_data *data, char *error);

int		create_philo_routine(t_philo *p);

void	ft_mutex_write(t_philo *p, char *str);

void	philo_sleep(t_philo *p);

void	philo_eat(t_philo *p);

t_bool	get_gameover(t_data *data, t_bool ac);

void	Monitor(t_data *data);

t_philo	*check_philo(t_data *data);


#endif
