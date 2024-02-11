/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:15:26 by zachamou          #+#    #+#             */
/*   Updated: 2024/02/11 12:15:08 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned int ft_atoi(const char *str)
{
    int     i;
    long   resultat; 
    
    resultat = 0;
    i = 0;
    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
        		resultat = resultat * 10 + str[i] - '0';
		i++;
	}
	if(resultat > 2147483647LL)
	{	
		ft_erro(2);
		return(EXIT_FAILURE);
    }
    return (resultat);
}

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead);
	if (i)
		ph->pa->stop = i;
	if (ph->pa->stop)
	{
		pthread_mutex_unlock(&ph->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->dead);
	return (0);
}


long int	get_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_erro(10);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
