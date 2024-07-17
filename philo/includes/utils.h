/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by lebartol          #+#    #+#             */
/*   Updated: 2024/07/17 15:40:55 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

typedef enum e_bool
{
	false,
	true
}	t_bool;

int		ft_atoi(const char *str);

long	ft_atol(const char *s);

t_bool	ft_is_string_numeric(const char *str);

int		ft_isdigit(int c);

int		ft_usleep(size_t milliseconds);

size_t	get_current_time(void);

#endif
