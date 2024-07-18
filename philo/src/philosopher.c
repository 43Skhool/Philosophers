/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 19:01:48 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	take_forks(t_philo *philo);

void philo_sleep(t_philo *p)
{
	ft_mutex_write(p, "is sleeping.");
	ft_usleep(p->data->time_to_sleep);
}

void philo_eat(t_philo *p)
{
	if (p->data->number_of_philosophers == 1)
		return ;

	if (take_forks(p) == false)
		return;
	
	ft_mutex_write(p, "took right fork.");
	ft_mutex_write(p, "took left fork.");
	ft_mutex_write(p, "is eating.");

	pthread_mutex_lock(&p->data->p_mutex);
	p->last_meal = get_current_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->p_mutex);

	ft_usleep(p->data->time_to_eat);

	pthread_mutex_unlock(&p->l_fork->fork);
	pthread_mutex_unlock(&p->r_fork->fork);
	p->r_fork->is_avaible = false;
	p->l_fork->is_avaible = true;

	philo_sleep(p);
	ft_mutex_write(p, "is thinking.");
}

t_bool	take_forks(t_philo *philo)
{
	int	f_R;
	int	f_L;

	if (philo->r_fork->is_avaible && philo->l_fork->is_avaible)
	{
		f_R = pthread_mutex_lock(&philo->r_fork->fork);
		f_L = pthread_mutex_lock(&philo->l_fork->fork);
		if (f_R != 0 || f_L != 0)
		{
			if (f_R != 0)
				pthread_mutex_unlock(&philo->r_fork->fork);
			if (f_L != 0)
				pthread_mutex_unlock(&philo->l_fork->fork);
			return (false);
		}
		philo->r_fork->is_avaible = false;
		philo->l_fork->is_avaible = true;
		return (true);
	}

	return (false);
}
