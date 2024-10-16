/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:37 by lebartol          #+#    #+#             */
/*   Updated: 2024/10/14 13:28:45 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philos(t_data *data);
static void	join_threads(t_data *data);

void	*free_all(t_data *data, char *error)
{
	if (error)
		printf("%s\n", error);
	if (!data)
		return (NULL);
	if (data->first_philo)
	{
		join_threads(data);
		free_philos(data);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->p_mutex);
	if (data)
		free(data);
	return (NULL);
}

static void	free_philos(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 0;
	if (!data->first_philo)
		return ;
	philo_tmp = data->first_philo;
	while (i < data->number_of_philosophers)
	{
		data->first_philo = philo_tmp->right_philo;
		pthread_mutex_destroy(&philo_tmp->r_fork->fork);
		pthread_mutex_destroy(&philo_tmp->philo_lock);
		free(philo_tmp->r_fork);
		free(philo_tmp);
		philo_tmp = data->first_philo;
		i++;
	}
}

static void	join_threads(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	philo_tmp = data->first_philo;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philo_tmp->thread_id, NULL);
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
}
