/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:14 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 17:19:54 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*check_philo(t_data *data);
int	check_meals(t_data *data);

void	Monitor(t_data *data)
{
	pthread_mutex_lock(&data->p_mutex);
	while (!check_philo(data) && !check_meals(data))
	{
		pthread_mutex_unlock(&data->p_mutex);
		usleep(500);
		pthread_mutex_lock(&data->p_mutex);
	}
	if (check_meals(data))
		ft_mutex_write(data->first_philo, "each philosopher is satisfied");
	else
		ft_mutex_write(check_philo(data), "has died of hunger.");
	pthread_mutex_unlock(&data->p_mutex);
	get_gameover(data, true);
}

int	check_meals(t_data *data)
{
	t_philo	*p;

	if (data->meals_count == -1)
		return (0);
	p = data->first_philo;
	if (p->meals_eaten < data->meals_count)
		return (0);
	if (p->right_philo)
		p = p->right_philo;
	while (p != data->first_philo)
	{
		if (p->meals_eaten < data->meals_count)
			return (0);
		if (p->right_philo)
			p = p->right_philo;
	}
	return (1);
}

t_philo	*check_philo(t_data *data)
{
	t_philo	*p;
	
	// pthread_mutex_lock(&data->p_mutex);
	p = data->first_philo;
	if ((int)(get_current_time() - p->last_meal) >= data->time_to_die)
		return (p);
	if (p->right_philo)
		p = p->right_philo;

	while (p != data->first_philo)
	{
		if ((int)(get_current_time() - p->last_meal) >= data->time_to_die)
			return (p);
		if (p->right_philo)
			p = p->right_philo;		
	}
	// pthread_mutex_unlock(&data->p_mutex);
	return (NULL);
}
