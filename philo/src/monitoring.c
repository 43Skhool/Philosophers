/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:14 by lebartol          #+#    #+#             */
/*   Updated: 2024/08/11 17:55:16 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal(t_philo *p)
{
	int	i;

	pthread_mutex_lock(&p->philo_lock);
	i = (p->meals_eaten < p->data->meals_count);
	pthread_mutex_unlock(&p->philo_lock);
	return (i);
}

int	check_meals(t_data *data)
{
	t_philo	*p;

	if (data->meals_count == -1)
		return (0);
	p = data->first_philo;
	if (check_meal(p))
		return (0);
	if (p->right_philo)
		p = p->right_philo;
	while (p != data->first_philo)
	{
		if (check_meal(p))
			return (0);
		if (p->right_philo)
			p = p->right_philo;
	}
	return (1);
}

int	check_death(t_philo *p)
{
	int			i;
	static int	y;

	if (p->id == 1)
		y = 0;
	pthread_mutex_lock(&p->philo_lock);
	i = ((int)(get_current_time() - p->last_meal) >= p->data->time_to_die + 5);
	y += (p->meals_eaten > p->data->meals_count && p->data->meals_count != -1);
	pthread_mutex_unlock(&p->philo_lock);
	if (y == p->data->number_of_philosophers)
		return (1);
	if (p->id == p->data->number_of_philosophers)
		y = 0;
	return (i);
}

t_philo	*check_philo(t_data *data)
{
	t_philo	*p;

	p = data->first_philo;
	if (check_death(p))
		return (p);
	if (p->right_philo)
		p = p->right_philo;
	while (p != data->first_philo)
	{
		if (check_death(p))
			return (p);
		if (p->right_philo)
			p = p->right_philo;
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	while (!check_philo(data))
	{
		usleep(2000);
	}
	if (check_meals(data))
		ft_mutex_write(data->first_philo, "each philosopher is satisfied");
	else
		ft_mutex_write(check_philo(data), "has died of hunger.");
	game_over(data);
}
