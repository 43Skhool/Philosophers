/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:37 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 17:47:18 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philos(t_data *data);

// error is used to print an OPTIONAL message error
//	for example during parsing
// Free all philosophers
// Check if data isn't null is just to handle possible error
//	during memory allocation
void	free_and_exit(t_data *data, char *error)
{
	if (error)
		printf("%s\n", error);
	if (data->first_philo)
		free_philos(data);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->p_mutex);
	//pthread_mutex_destroy(&data->game_lock);
	// free(data->write_lock);
	if (data)
		free(data);

	exit(0);
}

// Pass throw the list of philosophers and free each one
// Check if first_philo is null, in this case there would have been
//	an error during parsing
// Loop until i hasn't reach the number of philos beacause
//	doing while(philo_tmp) would result in a conditianl jump and infinite loop
// As in the allocation, is always freed the left side node of the current one
//	=> you step on and free the previous one
// Assing NULL to only one reference to philos in data just
//	to avoid conditional jump (is optional)
// l'ultimo filosofo quando lo liberi
static void	free_philos(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 0;
	if (!data->first_philo)
		return ;
	philo_tmp = data->first_philo;
	while (i < data->number_of_philosophers)
	{
		data->first_philo = philo_tmp->right_philo;
		pthread_join(philo_tmp->thread_id, NULL);
		pthread_mutex_destroy(&philo_tmp->r_fork->fork);
		free(philo_tmp->r_fork);
		free(philo_tmp);
		philo_tmp = data->first_philo;
		i++;
	}
}
