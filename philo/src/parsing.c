/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 15:40:55 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Used to check every single argc because all of them respect the same
//	rules and are of the same type
// Assign to target the value get by arg
// Check if string is numeric, it includes first sign: ++1: wrong, +1: ok
// Check with atol fi the number isn't bigger than int
//	beacuse it can't be checked just atoi, it would cast it with an overflow
// Assign the value to target parameter and return it
// Return the number alreay parsed or -1 if ther's some errors
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

// Returns data or exit the program bu free_and_free()
// Try to assign value to variable in data for each parameters
//	if an error occurs, the error is specific for each parameter
// Last, being optional is verified just when argc == 6
//	if isn't specified: -1
static t_data	*load_arguments(t_data *data, char *argv[], int argc)
{
	if (get_single_arg(&data->number_of_philosophers, argv[1]) == -1)
		free_and_exit(data, "Error\n number of philosophers not valid\n");
	if (get_single_arg(&data->time_to_die, argv[2]) == -1)
		free_and_exit(data, "Error\n time to die not valid\n");
	if (get_single_arg(&data->time_to_eat, argv[3]) == -1)
		free_and_exit(data, "Error\n time to eat not valid\n");
	if (get_single_arg(&data->time_to_sleep, argv[4]) == -1)
		free_and_exit(data, "Error\n time to live not valid\n");
	if (argc == 6)
	{
		if (get_single_arg(&data->meals_count, argv[5]) == -1)
			free_and_exit(data, "Error\n number of eating not valid\n");
	}
	else
		data->meals_count = -1;
	data->timestamp = get_current_time();
	return (data);
}

// Check argc
// Try and check malloc
// Get the values from argv
// Assign NULL to first_philo pointer to avoid future conditional jump
// TO DO spostare l'inizializzazione di DATA in una funzione apparte
t_data	*parse_arguments(int argc, char *argv[])
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
		free_and_exit(data, "Error\n wrong number of arguments\n");
	data = malloc(sizeof(t_data));
	if (!data)
		free_and_exit(data, "Error\n allocation failed\n");
	if (pthread_mutex_init(&data->write_lock, NULL) != 0
		|| pthread_mutex_init(&data->game_lock, NULL) != 0
		|| pthread_mutex_init(&data->p_mutex, NULL) != 0)
		free_and_exit(data, "Error\n writing lock allocation failed\n");
	data->first_philo = NULL;
	data->game_over = false;
	data = load_arguments(data, argv, argc);
	return (data);
}
