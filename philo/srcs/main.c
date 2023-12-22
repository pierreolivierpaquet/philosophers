/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:50:06 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/23 13:18:33 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (philo_min_max_argc_check(argc) == FAILURE)
		return (FAILURE);
	if (philo_environment(argc, argv) == FAILURE)
		return (FAILURE);
	if (philosophers(philo_env_pull()) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
