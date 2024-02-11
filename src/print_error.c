/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:35:46 by zachamou          #+#    #+#             */
/*   Updated: 2024/02/11 12:49:19 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    put_stderr(char *msg)
{
    write(2, "\033[1;31m", 7);
    write(2, msg, ft_strlen(msg));
    write(2, "\033[0m", 4);
}

void    ft_erro(int er_nb)
{
    if (er_nb == 1) 
    {
        put_stderr("Warning: you need 4 or 5 (option) arguments:\n"
               "./philo 1.[number_of_philosophers] 2.[time_to_die] "
               "3.[time_to_eat] 4.[time_to_sleep] | Optional arg: "
               "5.[nombre_de_repas_minimal_par_philosophe]\n");
    }
    else if (er_nb == 2)
        put_stderr("Warning: errors in the argument Only the numerical values are valid\n");      
    else if (er_nb == 3)
        put_stderr("Warning: errors in alloc\n"); 
    else if (er_nb == 4)
        put_stderr("Warning: Error pthread\n");
    else if (er_nb == 5)
        put_stderr("Warning: Error\n");
    else if (er_nb == 6)
        put_stderr("Warning: Error MUTEX\n");
    else if (er_nb == 10)
        put_stderr("Warning: Error dans les  nombre de args\n");
}
