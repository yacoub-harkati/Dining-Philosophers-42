/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:19:11 by yaharkat          #+#    #+#             */
/*   Updated: 2024/01/30 01:00:29 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (dead_loop(ph->data))
	{
		philo_eat(ph);
		philo_sleep(ph);
		philo_think(ph);
	}
	return (NULL);
}
