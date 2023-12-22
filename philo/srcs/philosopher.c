/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:50:03 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/25 15:17:59 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_philosophers_fill_data(t_philo_env *env, t_philosopher *philo, int i)
{
	if (env == NULL || philo == NULL)
		return (FAILURE);
	philo[i].state = ALIVE;
	philo[i].env = env;
	philo[i].tag = i + 1;
	philo[i].d_line = (long long)env->time_to_die;
	philo[i].cs1 = &env->chopsticks[i];
	if (i == env->philo_amt - 1)
		philo[i].cs2 = &env->chopsticks[DEFAULT];
	else
		philo[i].cs2 = &env->chopsticks[i + 1];
	philo[i].must_eat = env->must_eat_amt;
	philo[i].t_t_die = env->time_to_die;
	philo[i].t_t_slp = env->time_to_sleep;
	philo[i].t_t_eat = env->time_to_eat;
	return (SUCCESS);
}

int	philo_philosophers_init(t_philo_env *env)
{
	t_philosopher	*philo;
	int				n;
	int				i;

	if (env == NULL)
		return (FAILURE);
	philo = NULL;
	n = env->philo_amt;
	philo = philo_alloc(CALLOC, n, sizeof(*philo));
	if (philo == NULL)
		return (philo_err_msg("Allocating philosophers memory.", FD_ERR));
	env->philo = philo;
	i = -1;
	while (++i < n)
	{
		if (philo_philosophers_fill_data(env, philo, i) == FAILURE)
			return (philo_err_msg("Initializing philosopher.", FD_ERR));
	}
	return (SUCCESS);
}

int	philo_chopsticks_init(t_philo_env *env)
{
	t_cstick	*chopsticks;
	int			n;
	int			i;

	if (env == NULL)
		return (FAILURE);
	n = env->philo_amt;
	chopsticks = NULL;
	chopsticks = philo_alloc(CALLOC, n, sizeof(*chopsticks));
	if (chopsticks == NULL)
		return (philo_err_msg("Allocating chopsticks memory.", FD_ERR));
	env->chopsticks = chopsticks;
	i = 0;
	while (i < n)
	{
		chopsticks[i].state = DEFAULT;
		if (pthread_mutex_init(&chopsticks[i].cs_mutex, NULL) != SUCCESS)
			return (philo_err_msg("Initializing c.stick MUTEX.", FD_ERR));
		chopsticks[i].state = AVBL;
		i++;
	}
	return (SUCCESS);
}

int	philosophers(t_philo_env *env)
{
	if (env == NULL)
		return (FAILURE);
	if (philo_chopsticks_init(env) == FAILURE
		|| philo_philosophers_init(env) == FAILURE)
	{
		philo_env_free(&env);
		return (FAILURE);
	}
	if (philo_thread_init(env) == FAILURE
		|| philo_thread_join(env) == FAILURE)
	{
		philo_env_free(&env);
		return (FAILURE);
	}
	return (philo_env_free(&env));
}
