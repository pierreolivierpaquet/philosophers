/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:46:01 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/29 11:12:54 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	philo_fetch_time(void)
{
	static struct timeval	begin = {DEFAULT, DEFAULT};
	struct timeval			now;
	long long				clock;

	if ((begin.tv_sec) == DEFAULT && (begin.tv_usec == DEFAULT))
		gettimeofday(&begin, NULL);
	gettimeofday(&now, NULL);
	clock = (long long)((now.tv_sec * S_MS) - (begin.tv_sec * S_MS)) + 
		(long long)((now.tv_usec * US_MS) - (begin.tv_usec * US_MS));
	return (clock);
}

int	philo_long_usleep(t_philosopher *philo, long long delay)
{
	long long	buffer;
	long long	temp;

	temp = delay;
	buffer = 1000;
	if (delay > 2000)
	{
		while (buffer < (temp - buffer))
		{
			usleep(buffer);
			buffer *= 1.1;
			temp -= buffer;
			if (philo_death_check(philo) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

void	philo_usleep(t_philosopher *philo, long long delay)
{
	long long	now;
	long long	free_to_go;

	now = philo_fetch_time();
	free_to_go = now + delay;
	if ((free_to_go > philo->d_line) && philo->state == ALIVE
		&& (now < philo->d_line))
	{
		usleep((philo->d_line - now) * MS_US);
		philo_death_flagger(philo);
	}
	else if (philo->state == ALIVE)
	{
		if (philo_long_usleep(philo, delay) == FAILURE)
			return ;
		usleep((delay * MS_US) * DELAY_MARGIN);
		while (philo_fetch_time() < free_to_go)
			usleep(100);
	}
	return ;
}
