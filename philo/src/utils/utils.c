/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:14 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/16 15:36:41 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_mutex_write(t_philo *p, char *str)
{
	while (pthread_mutex_trylock(&p->data->write_lock))
		usleep(100);
	if (p->data->game_over)
	{
		pthread_mutex_unlock(&p->data->write_lock);
		return ;
	}
	printf("[%zu]\t%d\t%s\n",(get_current_time() - p->birthday), p->id, str);
	pthread_mutex_unlock(&p->data->write_lock);
}

// TODO in caso di errore nel gettimeofday non sarebbe meglio uscire direttamente con la funzione
// free_adn_exit()? so che non succede mai ma se dovesse succedere si sfanculerebbe tutto??
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//TO DO avevi messo 500 ma ho visto che molti usano 1000 
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(1000);
	return (0);
}

//start from 1 and and at num of philo just to follow id order
void	display_table(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 1;
	// if (data->number_of_philosophers == 1)
	// {
	// 	printf("Current id:%i\n", data->first_philo->id);
	// }
	printf("%p writelock\n", &data->write_lock);
	printf("%p gameover\n", &data->game_over);
	philo_tmp = data->first_philo;
	while (i <= data->number_of_philosophers)
	{
		printf("%p <- Current id:%i -> %p\n", &philo_tmp->l_fork->fork, philo_tmp->id, &philo_tmp->r_fork->fork);
		printf("on his left id: %p, ", &philo_tmp->left_philo->id);
		printf("on his rigth id: %p\n", &philo_tmp->right_philo->id);
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
}

t_bool	get_gameover(t_data *data, t_bool action)
{
	t_bool ret;

	pthread_mutex_lock(&data->game_lock);
	if (action == true)
		data->game_over = true;
	ret = data->game_over;
	pthread_mutex_unlock(&data->game_lock);
	return (ret);
}
