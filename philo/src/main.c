/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:45:02 by lebartol          #+#    #+#             */
/*   Updated: 2024/10/14 13:28:29 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_game(t_philo *p)
{
	int	i;

	pthread_mutex_lock(&p->philo_lock);
	i = p->game;
	pthread_mutex_unlock(&p->philo_lock);
	return (i);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2)
		philo_sleep(philo);
	while (get_game(philo))
	{
		philo_eat(philo);
	}
	return (NULL);
}

int	create_threads(t_data *data)
{
	t_philo	*p;

	p = data->first_philo;
	if (create_philo_routine(p))
		return (1);
	p = p->right_philo;
	while (p != data->first_philo)
	{
		if (create_philo_routine(p))
			return (1);
		p = p->right_philo;
	}
	return (0);
}

int	create_philo_routine(t_philo *p)
{
	if (pthread_create(&p->thread_id, NULL, philo_routine, p))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = parse_arguments(argc, argv);
	if (!data)
		return (1);
	data = initialize_table(data);
	if (!data)
		return (1);
	if (!create_threads(data))
		monitor(data);
	monitor(data);
	free_all(data, NULL);
}
