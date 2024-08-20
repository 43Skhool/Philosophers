/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:14 by lebartol          #+#    #+#             */
/*   Updated: 2024/08/11 14:25:33 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_write(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->data->write_lock);
	if (!get_game(p))
	{
		pthread_mutex_unlock(&p->data->write_lock);
		return ;
	}
	printf("[%zu]\t%d\t%s\n", (get_current_time() - p->birthday), p->id, str);
	pthread_mutex_unlock(&p->data->write_lock);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(1000);
	return (0);
}

void	display_table(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 1;
	printf("%p writelock\n", &data->write_lock);
	printf("%p gameover\n", &data->game_over);
	philo_tmp = data->first_philo;
	while (i <= data->number_of_philosophers)
	{
		printf("%p <- Current id:%i -> %p\n", &philo_tmp->l_fork->is_avaible,
			philo_tmp->id, &philo_tmp->r_fork->is_avaible);
		printf("%p <- Current id:%i -> %p\n", &philo_tmp->l_fork->fork,
			philo_tmp->id, &philo_tmp->r_fork->fork);
		printf("on his left id: %p, ", &philo_tmp->left_philo->id);
		printf("on his rigth id: %p\n", &philo_tmp->right_philo->id);
		printf("lock no.%p\n", &philo_tmp->philo_lock);
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
}

t_bool	get_gameover(t_data *data, t_bool action)
{
	t_bool	ret;

	pthread_mutex_lock(&data->game_lock);
	if (action == true)
		data->game_over = true;
	ret = data->game_over;
	pthread_mutex_unlock(&data->game_lock);
	return (ret);
}
