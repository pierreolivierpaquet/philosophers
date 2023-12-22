/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:19:48 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/29 11:13:05 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_takes_cs(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->cs1->cs_mutex);
	philo_msg(philo, TAKE_CS);
	pthread_mutex_lock(&philo->cs2->cs_mutex);
	philo_msg(philo, TAKE_CS);
	return (SUCCESS);
}

int	philo_returns_cs(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->cs1->cs_mutex);
	pthread_mutex_unlock(&philo->cs2->cs_mutex);
	pthread_mutex_lock(&philo->env->csticks_mutex);
	philo->cs1->state = AVBL;
	philo->cs2->state = AVBL;
	pthread_mutex_unlock(&philo->env->csticks_mutex);
	return (SUCCESS);
}

int	philo_eating(t_philosopher *philo)
{
	if (philo_death_check(philo) == FAILURE)
		return (FAILURE);
	if (philo_before_eating(philo) == FAILURE)
		return (FAILURE);
	if (philo_takes_cs(philo) == FAILURE)
		return (FAILURE);
	philo_msg(philo, EAT);
	philo->d_line = (philo_fetch_time() + philo->t_t_die);
	philo_usleep(philo, philo->t_t_eat);
	if (philo->must_eat >= 0)
	{
		philo->must_eat--;
		if (philo->must_eat == 0)
		{
			philo->state = SATIATED;
			philo_returns_cs(philo);
			return (ALIVE + SATIATED);
		}
	}
	philo_returns_cs(philo);
	return (SUCCESS);
}

int	philo_sleeping(t_philosopher *philo)
{
	if (philo->state != ALIVE)
		return (FAILURE);
	philo_msg(philo, SLEEP);
	philo_usleep(philo, philo->t_t_slp);
	return (SUCCESS);
}

int	philo_thinking(t_philosopher *philo)
{
	if (philo->state != ALIVE)
		return (FAILURE);
	philo_msg(philo, THINK);
	return (SUCCESS);
}
