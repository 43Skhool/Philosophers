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

int	check_meal(t_philo *p)
{
	int i;
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
	int i;
	pthread_mutex_lock(&p->philo_lock);
	i = ((int)(get_current_time() - p->last_meal) >= p->data->time_to_die);
	pthread_mutex_unlock(&p->philo_lock);
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

void	set_game_over(t_philo *p)
{
	pthread_mutex_lock(&p->philo_lock);
	p->game = 0;
	pthread_mutex_unlock(&p->philo_lock);
}

void	game_over(t_data *data)
{
	t_philo	*p;

	p = data->first_philo;
	set_game_over(p);
	if (p->right_philo)
		p = p->right_philo;
	while (p != data->first_philo)
	{
		set_game_over(p);
		if (p->right_philo)
			p = p->right_philo;		
	}
}

void	Monitor(t_data *data)
{
	while (!check_philo(data) && !check_meals(data))
	{
		usleep(2000);
	}
	if (check_meals(data))
		ft_mutex_write(data->first_philo, "each philosopher is satisfied");
	else
		ft_mutex_write(check_philo(data), "has died of hunger.");
	//get_gameover(data, true);
	game_over(data);
}
