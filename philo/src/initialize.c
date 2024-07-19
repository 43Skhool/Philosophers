/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:53:56 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 17:34:57 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(t_data *data, int id, t_philo *left_philo);
static t_bool	distribute_forks(t_data *data);
static t_fork	*new_fork(t_data *data);

// Used to allocate philosophers and forks
// i starts from 1 beacause philos id must start from 1
// Crete 1° philo with NULL as left_philosopher beacause is the first
//	=> his left philo will be assigned at the end
// It's used the RIGHT CREATION
//	=> First of all is created first node and assigned to first_philo in data
//		Each time is creted the next one (on his right) and connected
//		with the current one
// In the end, to close the "chain" is conneceted the current node
//	with the first one
t_data	*initialize_table(t_data *data)
{
	t_philo *philo_tmp;
	int		i;

	i = 1;
	philo_tmp = new_philo(data, i++, NULL);
	data->first_philo = philo_tmp;
	while (i <= data->number_of_philosophers)
	{
		philo_tmp->right_philo = new_philo(data, i, philo_tmp);
		philo_tmp->right_philo->left_philo = philo_tmp;
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
	philo_tmp->right_philo = data->first_philo;
	data->first_philo->left_philo = philo_tmp;
	distribute_forks(data);
	return (data);
}

// Just left node in parameters because right creation is used
//	=> assign just the left one because you don't know what it will be later
static t_philo	*new_philo(t_data *data, int id, t_philo *left_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo || pthread_mutex_init(&philo->philo_lock, NULL))
		free_and_exit(data, "Error\n allocation failed");
	philo->id = id;

	if (left_philo)
	{
		// philo->l_fork = &left_philo->r_fork;
		philo->left_philo = left_philo;
	}
	philo->birthday =  data->timestamp;
	philo->game = 1;
	// adesso che abbiamo data birthday non serve ma non ho voglia di riscrivere i metodi del write
	philo->last_meal = get_current_time();
	philo->meals_eaten = 0;
	philo->data = data;
	return (philo);
}

static t_bool	distribute_forks(t_data *data)
{
	t_philo	*philo;
	int		i;
	t_fork	*fork;

	philo = data->first_philo;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		fork = new_fork(data);
		philo->r_fork = fork;
		philo = philo->right_philo;
		philo->l_fork = fork;
		i++;
	}
	return (true);
}

static t_fork	*new_fork(t_data *data)
{
	t_fork	*new_fork;

	new_fork = malloc(sizeof(t_fork));
	if (!new_fork)
		free_and_exit(data, "Error\n fork allocation failed");
	if (pthread_mutex_init(&new_fork->fork, NULL))
		free_and_exit(data, "Error\n fork allocation failed");
	new_fork->is_avaible = true;
	return (new_fork);
}
