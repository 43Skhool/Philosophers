/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:45:02 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 19:01:48 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_game(t_philo *p)
{
	int i;
	pthread_mutex_lock(&p->philo_lock);
	i = p->game;
	pthread_mutex_unlock(&p->philo_lock);
	return (i);
}

void	*philo_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (philo->id % 2)
		philo_sleep(philo);
	while (get_game(philo))
	{
		philo_eat(philo);
	}
	return (NULL);
}

//TODO spostare questa cosa direttamente in initialize_table()
int create_threads(t_data *data)
{
	t_philo *p;
	
	pthread_mutex_lock(&data->p_mutex);
	p = data->first_philo;
	if (create_philo_routine(p))
	{
		pthread_mutex_unlock(&data->p_mutex);
		return (1);
	}
	p = p->right_philo;
	while (p != data->first_philo)
	{
		if (create_philo_routine(p))
		{
			pthread_mutex_unlock(&data->p_mutex);
			return (1);
		}
		p = p->right_philo;
	}
	pthread_mutex_unlock(&data->p_mutex);
	return (0);
}

int create_philo_routine(t_philo *p)
{
	if (pthread_create(&p->thread_id, NULL, philo_routine, p))
		return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	t_data		*data;

	data = parse_arguments(argc, argv);
	data = initialize_table(data);

	if (!create_threads(data))
		Monitor(data);

	// Monitor(data);

	//display_table(data);
	free_and_exit(data, NULL);
}
