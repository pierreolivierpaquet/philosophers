/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:05:21 by ppaquet           #+#    #+#             */
/*   Updated: 2023/08/23 10:19:59 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_strlen(const char *s)
{
	int	l;
	int	i;

	i = 0;
	l = 0;
	while (s[i++] != '\0')
		l++;
	return (l);
}

void	philo_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}

void	philo_putstr_fd(const char *s, int fd)
{
	int	i;
	int	l ;

	i = 0;
	l = philo_strlen(s);
	while (i < l)
		philo_putchar_fd(s[i++], fd);
	return ;
}

void	philo_putendl_fd(const char *s, int fd)
{
	philo_putstr_fd(s, fd);
	philo_putchar_fd('\n', fd);
	return ;
}

int	philo_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*p1;
	unsigned char	*p2;

	if (!s1 || !s2)
		return (0);
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while ((p1[i] == p2[i]) && (p1[i] != '\0' || p2[i] != '\0'))
	{
		i++;
		if (p1[i] == '\0' || p2[i] == '\0')
			return (SUCCESS);
	}
	return (FAILURE);
}
