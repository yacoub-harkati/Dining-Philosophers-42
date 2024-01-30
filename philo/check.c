/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:34:10 by yaharkat          #+#    #+#             */
/*   Updated: 2024/01/30 00:32:19 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		print_error_exit("Wrong number of arguments (Expected 5 or 6).\n");
	while (++i < ac)
		check_is_number(av[i], i);
}

void	check_is_number(char *str, int i)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (!ft_isdigit(str[index]))
		{
			printf(RED "Error: " RESET);
			printf("Argument %d ('%s') is not valid (Expected u32).\n", i, str);
			exit(EXIT_FAILURE);
		}
	}
}

bool	check_all_philo_eat(t_data *data, bool print)
{
	int	i;

	i = -1;
	if (!data->num_of_eat)
		return (false);
	pthread_mutex_lock(&data->sync_mutex);
	while (++i < data->num_of_philo)
	{
		if (data->philo[i].eat_count < data->num_of_eat)
		{
			pthread_mutex_unlock(&data->sync_mutex);
			return (false);
		}
	}
	pthread_mutex_unlock(&data->sync_mutex);
	if (print)
		print_message(data->philo, OVER);
	return (true);
}

bool	check_any_philo_died(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = data->philo;
	while (++i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->sync_mutex);
		if (philos[i].is_dead == true)
		{
			pthread_mutex_unlock(&data->sync_mutex);
			return (true);
		}
		if (get_current_time()
			- philos[i].last_eat > philos[i].data->time_to_die)
		{
			philos[i].is_dead = true;
			pthread_mutex_unlock(&data->sync_mutex);
			print_message(&philos[i], DIED);
			return (true);
		}
		pthread_mutex_unlock(&data->sync_mutex);
	}
	return (false);
}

void	check_input_error(t_data *data)
{
	int		i;
	char	*s;

	s = "number_of_philosophers should be between 1 and 200 (inclusive).\n";
	i = 0;
	while (++i < 5)
	{
		if (i == 1 && (data->num_of_philo == 0 || data->num_of_philo > 200))
			print_error_exit(s);
		else if (i == 2 && data->time_to_die < 60)
			print_error_exit("time_to_die should be larger than 60ms.\n");
		else if (i == 3 && data->time_to_eat < 60)
			print_error_exit("time_to_eat should be larger than 60ms.\n");
		else if (i == 4 && data->time_to_sleep < 60)
			print_error_exit("time_to_sleep should be larger than 60ms.\n");
	}
}
