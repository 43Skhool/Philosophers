/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by lebartol          #+#    #+#             */
/*   Updated: 2024/08/11 14:24:05 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	take_forks(t_philo *philo);

void	philo_sleep(t_philo *p)
{
	ft_mutex_write(p, "is sleeping.");
	ft_usleep(p->data->time_to_sleep);
}

void	philo_eat(t_philo *p)
{
	if (p->data->number_of_philosophers == 1)
		return ;
	if (p->data->number_of_philosophers == p->id)
	{
		pthread_mutex_lock(&p->r_fork->fork);
		pthread_mutex_lock(&p->l_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&p->l_fork->fork);
		pthread_mutex_lock(&p->r_fork->fork);
	}
	ft_mutex_write(p, "took right fork.");
	ft_mutex_write(p, "took left fork.");
	ft_mutex_write(p, "is eating.");
	pthread_mutex_lock(&p->philo_lock);
	p->last_meal = get_current_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->philo_lock);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(&p->l_fork->fork);
	pthread_mutex_unlock(&p->r_fork->fork);
	philo_sleep(p);
	ft_mutex_write(p, "is thinking.");
}

t_bool	take_forks(t_philo *philo)
{
	int	f_r;
	int	f_l;

	if (philo->r_fork->is_avaible && philo->l_fork->is_avaible)
	{
		f_r = pthread_mutex_lock(&philo->r_fork->fork);
		f_l = pthread_mutex_lock(&philo->l_fork->fork);
		if (f_r != 0 || f_l != 0)
		{
			if (f_r != 0)
				pthread_mutex_unlock(&philo->r_fork->fork);
			if (f_l != 0)
				pthread_mutex_unlock(&philo->l_fork->fork);
			return (false);
		}
		philo->r_fork->is_avaible = true;
		philo->l_fork->is_avaible = true;
		return (true);
	}
	return (false);
}
