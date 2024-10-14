/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by lebartol          #+#    #+#             */
/*   Updated: 2024/10/14 13:28:19 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_single_arg(int *taget, char *arg)
{
	if (!ft_is_string_numeric(arg))
		return (-1);
	if (ft_atol(arg) < INT_MIN || ft_atol(arg) > INT_MAX)
		return (-1);
	*taget = ft_atoi(arg);
	if (*taget <= 0)
		return (-1);
	return (*taget);
}

static t_data	*load_arguments(t_data *data, char *argv[], int argc)
{
	if (get_single_arg(&data->number_of_philosophers, argv[1]) == -1)
		return (free_all(data, "Error\n number of philosophers not valid\n"));
	if (get_single_arg(&data->time_to_die, argv[2]) == -1)
		return (free_all(data, "Error\n time to die not valid\n"));
	if (get_single_arg(&data->time_to_eat, argv[3]) == -1)
		return (free_all(data, "Error\n time to eat not valid\n"));
	if (get_single_arg(&data->time_to_sleep, argv[4]) == -1)
		return (free_all(data, "Error\n time to live not valid\n"));
	if (argc == 6)
	{
		if (get_single_arg(&data->meals_count, argv[5]) == -1)
			return (free_all(data, "Error\n number of eating not valid\n"));
	}
	else
		data->meals_count = -1;
	data->timestamp = get_current_time();
	return (data);
}

t_data	*parse_arguments(int argc, char *argv[])
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
		return (free_all(data, "Error\n wrong number of arguments\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (free_all(data, "Error\n allocation failed\n"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0
		|| pthread_mutex_init(&data->game_lock, NULL) != 0
		|| pthread_mutex_init(&data->p_mutex, NULL) != 0)
		return (free_all(data, "Error\n writing lock allocation failed\n"));
	data->first_philo = NULL;
	data->game_over = false;
	data = load_arguments(data, argv, argc);
	return (data);
}
