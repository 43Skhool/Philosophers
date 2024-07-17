/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/16 13:09:20 by tfalchi          ###   ########.fr       */
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
	pthread_mutex_lock(&p->r_fork);
	pthread_mutex_lock(p->l_fork);
	ft_mutex_write(p, "took right fork.");
	ft_mutex_write(p, "took left fork.");
	ft_mutex_write(p, "is eating.");
	p->last_meal = get_current_time();
	p->meals_eaten++;
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(&p->r_fork);
}
