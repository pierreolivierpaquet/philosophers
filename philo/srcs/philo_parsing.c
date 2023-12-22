/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:50:01 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/25 16:04:11 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_min_max_argc_check(int argc)
{
	if (argc < MIN_ARG)
		return (philo_err_msg("Missing argument(s). \
\033[3;33m(See instructions below)\033[0m\n\
\tEnter 4-5 as per the \
following format:\n\tMandatory (4): <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>\n\t\
Optionnal (5th): <number_of_times_each_philosophers_must_eat>", FD_ERR));
	if (argc > MAX_ARG)
		return (philo_err_msg("Too many arguments.", FD_ERR));
	return (SUCCESS);
}

int	philo_args_retain(t_philo_env *env, int ac, char **av)
{
	env->ac = ac;
	env->av = av;
	return (SUCCESS);
}

int	philo_args_check(t_philo_env *env)
{
	if (env == NULL)
		return (philo_err_msg(NULL, FD_ERR));
	if ((int)env->philo_amt <= 0)
		return (philo_err_msg("Invalid <number_of_philosophers>.", FD_ERR));
	if ((int)env->philo_amt > 300)
		return (philo_err_msg("<number_of_philosophers> is too high.", FD_ERR));
	if ((int)env->time_to_die < 10)
		return (philo_err_msg("Invalid <time_to_die>.", FD_ERR));
	if ((int)env->time_to_eat < 10)
		return (philo_err_msg("Invalid <time_to_eat>.", FD_ERR));
	if ((int)env->time_to_sleep < 10)
		return (philo_err_msg("Invalid <time_to_sleep>.", FD_ERR));
	if (env->ac == 6)
	{
		if ((int)env->must_eat_amt < 0)
			return (philo_err_msg("<number_of_times_each_philosopher_must_eat\
> argument.", FD_ERR));
	}
	return (SUCCESS);
}

int	philo_args_parse(t_philo_env *env)
{
	int	i;

	if (env == NULL || env->av == NULL
		|| env->ac < MIN_ARG || env->ac > MAX_ARG)
		return (FAILURE);
	i = 0;
	env->philo_amt = philo_ascii_to_num(env->av[++i]);
	env->time_to_die = philo_ascii_to_num(env->av[++i]);
	env->time_to_eat = philo_ascii_to_num(env->av[++i]);
	env->time_to_sleep = philo_ascii_to_num(env->av[++i]);
	if (env->ac == MAX_ARG)
		env->must_eat_amt = philo_ascii_to_num(env->av[++i]);
	else
		env->must_eat_amt = NO_EAT_LIMIT;
	return (philo_args_check(env));
}
