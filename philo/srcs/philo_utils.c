/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:53:05 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/25 15:28:02 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_death_flagger(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->env->death_mutex);
	if (philo->env->death == NULL)
	{
		philo->state = DEAD;
		philo->env->death = philo;
		pthread_mutex_unlock(&philo->env->death_mutex);
		philo_msg(philo, DIE);
		return ;
	}
	pthread_mutex_unlock(&philo->env->death_mutex);
	return ;
}

int	philo_death_check(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->env->death_mutex);
	if (philo->env->death != NULL)
	{
		pthread_mutex_unlock(&philo->env->death_mutex);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->env->death_mutex);
	return (SUCCESS);
}

int	philo_chopsticks_availability(t_philosopher *philo)
{
	int	availability;

	availability = FAILURE;
	if (philo->cs1 == philo->cs2)
	{
		philo_msg(philo, TAKE_CS);
		philo_usleep(philo, philo->t_t_die);
		philo_death_flagger(philo);
		return (availability);
	}
	pthread_mutex_lock(&philo->env->csticks_mutex);
	if (philo->cs1->state == AVBL && philo->cs2->state == AVBL)
	{
		philo->cs1->state = UVBL;
		philo->cs2->state = UVBL;
		availability = SUCCESS;
	}
	pthread_mutex_unlock(&philo->env->csticks_mutex);
	return (availability);
}

int	philo_before_eating(t_philosopher *philo)
{
	usleep(200);
	while (philo_chopsticks_availability(philo) == FAILURE
		|| philo->d_line <= philo_fetch_time())
	{
		if (philo->d_line <= philo_fetch_time())
		{
			philo_death_flagger(philo);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
