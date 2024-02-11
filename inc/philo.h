/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zack <zack@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:20:38 by zachamou          #+#    #+#             */
/*   Updated: 2024/02/11 12:37:41 by zack             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define WHITE   "\033[37m"


#define TAKE_F  GREEN "Has taken fork🍴\n" RESET
#define DROP_F  YELLOW "Has dropped fork🫳🍴\n" RESET
#define EAT     BLUE "Is eating🍵\n" RESET
#define SLEEP   MAGENTA "SLEEP\n" RESET
#define DEAD    RED "Is DEAD 💀:c\n" RESET
#define THINK   CYAN "Is thinking🤔\n" RESET

typedef struct s_data
{
	int						total;
	int						die;
	int						eat;
	int						sleep;
	int						m_eat;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_p_finish;
	int						stop;
}							t_data;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*r_f;
	pthread_mutex_t			l_f;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
	t_data					*pa;
}							t_philo;

typedef struct s_p
{
	t_philo					*ph;
	t_data					args;
}							t_p;

void			activity(t_philo *ph);
void			ft_usleep(long int time_in_ms);
void			*thread(void *data);
int				check_death(t_philo *ph, int i);
int 			trown_thread(t_p *p);
long int		get_time(void);
int 			init_data_philo(t_p *p);
int 			init_nb_philo(t_p *p);
int				maneg_args(int argc, char **argv, t_p *p);
int				trown_args(int argc, char **argv, t_p *p);
size_t			ft_strlen(char *str);
void    			ft_erro(int er_nb);
unsigned int	ft_atoi(const char *str);
int 			ic_no_numeric(char **av);
void			write_status(char *str, t_philo *ph);



#endif 
