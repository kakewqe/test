/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:20:22 by zachamou          #+#    #+#             */
/*   Updated: 2024/02/11 12:46:09 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death2(t_p *p)
{
	pthread_mutex_lock(&p->args.dead);
	if (p->args.stop)
	{
		pthread_mutex_unlock(&p->args.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->args.dead);
	return (0);
}

void	stop(t_p *p)
{
	int	i;

	i = -1;
	while (!check_death2(p))
		ft_usleep(1);
	while (++i < p->args.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->args.write_mutex);
	i = -1;
	while (++i < p->args.total)
		pthread_mutex_destroy(&p->ph[i].l_f);
	if (p->args.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->args.m_eat);
	free(p->ph);
}

int main(int argc, char **argv)
{
    t_p p;
    
    if ((maneg_args(argc, argv, &p)) == 1)
        return (EXIT_FAILURE);
    p.ph = malloc(p.args.total * sizeof(t_philo));
    if(!p.ph)
    {
        ft_erro(3);
        return(1);
    }
    if (!init_data_philo(&p) || !trown_thread(&p))
	{
		free(p.ph);
		return (0);
	}
    stop(&p);
    return (0);
}

    
    
