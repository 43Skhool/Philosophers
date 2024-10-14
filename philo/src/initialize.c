/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:53:56 by lebartol          #+#    #+#             */
/*   Updated: 2024/10/14 13:28:35 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(t_data *data, int id, t_philo *left_philo);
static t_bool	distr_forks(t_data *data);
static t_fork	*new_fork(t_data *data);

t_data	*initialize_table(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 1;
	philo_tmp = new_philo(data, i++, NULL);
	if (!philo_tmp)
		return (NULL);
	data->first_philo = philo_tmp;
	while (i <= data->number_of_philosophers)
	{
		philo_tmp->right_philo = new_philo(data, i, philo_tmp);
		if (!philo_tmp->right_philo)
			return (NULL);
		philo_tmp->right_philo->left_philo = philo_tmp;
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
	philo_tmp->right_philo = data->first_philo;
	data->first_philo->left_philo = philo_tmp;
	distr_forks(data);
	if (!data->first_philo->r_fork)
		return (free_all(data, "Error\n fork allocation failed"));
	return (data);
}

static t_philo	*new_philo(t_data *data, int id, t_philo *left_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo || pthread_mutex_init(&philo->philo_lock, NULL))
		return (free_all(data, "Error\n allocation failed"));
	philo->id = id;
	if (left_philo)
		philo->left_philo = left_philo;
	philo->birthday = data->timestamp;
	philo->game = 1;
	philo->last_meal = get_current_time();
	philo->meals_eaten = 0;
	philo->data = data;
	return (philo);
}

static t_bool	distr_forks(t_data *data)
{
	t_philo	*philo;
	int		i;
	t_fork	*fork;

	philo = data->first_philo;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		fork = new_fork(data);
		if (!fork)
			return (false);
		philo->r_fork = fork;
		philo = philo->right_philo;
		philo->l_fork = fork;
		i++;
	}
	return (true);
}

static t_fork	*new_fork(t_data *data)
{
	t_fork	*new_f;

	new_f = malloc(sizeof(t_fork));
	if (!new_f)
		return (free_all(data, "Error\n fork allocation failed"));
	if (pthread_mutex_init(&new_f->fork, NULL))
		return (free_all(data, "Error\n fork allocation failed"));
	new_f->is_avaible = true;
	return (new_f);
}
