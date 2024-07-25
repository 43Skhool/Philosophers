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

int	check_meal(t_philo *p)
{
	int i;
	//pthread_mutex_lock(&p->philo_lock);
	i = (p->meals_eaten < p->data->meals_count);
	//pthread_mutex_unlock(&p->philo_lock);
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
	//pthread_mutex_lock(&p->philo_lock);
	i = ((int)(get_current_time() - p->last_meal) >= p->data->time_to_die);
	//pthread_mutex_unlock(&p->philo_lock);
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

// 1 someone is death, 2 all are satisfied, 0 keep going
int check_single_philo(t_philo	*philo)
{
	int result;

	result = 0;
	pthread_mutex_lock(&philo->philo_lock);

	if (check_death(philo))
		result = 1;
	
	if (philo->data->meals_count != -1)
		if (check_meal(philo))
			result = 2;

	pthread_mutex_unlock(&philo->philo_lock);

	return result;
}

//return death philo or null if all are satisfied
// null + 1 if 
t_philo	*Check(t_data	*data)
{
	t_philo	*p;

////ERRORE QUANDO NON è SPECIFICATO MEALS_COUNT!!
	
	p = data->first_philo;
	if (check_single_philo(p) != 0)
		return (p);
	if (p->right_philo)
		p = p->right_philo;
	while (p != data->first_philo)
	{
		if (check_single_philo(p) != 0)
			return (p);
		if (p->right_philo)
			p = p->right_philo;
	}
	return (NULL + 3);
}

// 1 someone is death, 2 all are satisfied, 0 keep going
int manage_error(t_data *data, int code, t_philo *died_philo)
{
	if (code == 0)
		return (0);

	if (code == 1)
		ft_mutex_write(died_philo, "has died of hunger.");
	
	if (code == 2)
		ft_mutex_write(data->first_philo, "each philosopher is satisfied");

	game_over(data);
	return (1);
}

void	Monitor(t_data *data)
{
	t_philo	*p;

	while (true)
	{
		usleep(2000);

		p = data->first_philo;

		if (manage_error (data, check_single_philo(p), p) == 1)
			break;

		if (p->right_philo)
			p = p->right_philo;

		while (p != data->first_philo)
		{
			if (manage_error (data, check_single_philo(p), p) == 1)
				break;

			if (p->right_philo)
				p = p->right_philo;
		}

		p = NULL;
	}
	
	// ft_mutex_write(data->first_philo, "each philosopher is satisfied");
	// //get_gameover(data, true);
	game_over(data);
}
