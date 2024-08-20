/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:20:56 by tfalchi           #+#    #+#             */
/*   Updated: 2024/08/11 14:27:30 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
