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


void philo_sleep(t_philo *p)
{
	ft_mutex_write(p, "is sleeping.");
	ft_usleep(p->data->time_to_sleep);
}

void philo_eat(t_philo *p)
{
	if (p->data->number_of_philosophers == 1)
		return ;
	if (p->id % 2)
	{
		pthread_mutex_lock(&p->l_fork->fork);
		pthread_mutex_lock(&p->r_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&p->r_fork->fork);
		pthread_mutex_lock(&p->l_fork->fork);
	}
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
}
