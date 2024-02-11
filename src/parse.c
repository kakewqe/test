/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:15:20 by zachamou          #+#    #+#             */
/*   Updated: 2024/02/11 11:27:18 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int ic_no_numeric(char **av)
{
    int i;
    int j;

    i = 1;
    while(av[i])
    {
        j = 0;
        while(av[i][j])
        {
            if (!(av[i][j] >= '0' && av[i][j] <= '9'))
                return(1);
            j++;
        }
        i++;
    }
    return(0);
}

int verif_arg(int ac, char **argv, t_p *p)
{
    if (p->args.total <= 1 || p->args.total >= 201 || p->args.eat <= 0 || p->args.sleep <= 0)
    {     
        ft_erro(10);
        return (1);
    }
    if (ac == 6 && p->args.m_eat <= 0)
    {        
        ft_erro(10);
        return (1);
    }
    return (0);
}


int maneg_args(int argc, char **argv, t_p *p)
{     
    if(trown_args(argc, argv, p))
        return (1); // Si trown_args renvoie 1 (erreur), alors retourne 1
    if(verif_arg(argc, argv, p))   
        return (1); // Si verif_arg renvoie 1 (erreur), alors retourne 1
    return (0); // Si tout est OK, retourne 0
}