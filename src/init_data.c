
#include "../inc/philo.h"

void	init_mutex(t_p *p)
{
	pthread_mutex_init(&p->args.write_mutex, NULL);
	pthread_mutex_init(&p->args.dead, NULL);
	pthread_mutex_init(&p->args.time_eat, NULL);
	pthread_mutex_init(&p->args.finish, NULL);
}

int init_data_philo(t_p *p)
{
    int i;
    i = 0;
    p->args.start_t = get_time();
    p->args.stop = 0;
    p->args.nb_p_finish = 0;
    init_mutex(p);
    while(i < p->args.total)
    {
        p->ph[i].id = i + 1;
		p->ph[i].ms_eat = p->args.start_t;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].r_f = NULL;
        pthread_mutex_init(&p->ph[i].l_f, NULL);
        if (i == p->args.total - 1)
			p->ph[i].r_f = &p->ph[0].l_f;
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f;
		i++;
	}
	return (1);
}

int trown_thread(t_p *p)
{
    int i;

    i = 0;
    while(i < p->args.total)
    {
        p->ph[i].pa = &p->args;
        if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
                ft_erro(4);
        i++;
    }
    return (1);   
}

int trown_args(int argc, char **argv, t_p *p)
{    if (!(argc == 5 || argc == 6))
    {
        ft_erro(1);
        return(1);
    }
    if(ic_no_numeric(argv))
    {
        ft_erro(2);
        return (1);
    }
    else
    {
        p->args.total = ft_atoi(argv[1]);
        p->args.die = ft_atoi(argv[2]);
        p->args.eat = ft_atoi(argv[3]);
        p->args.sleep = ft_atoi(argv[4]);
        p->args.m_eat = -1;
        if (argc == 6)
            p->args.m_eat = ft_atoi(argv[5]);
    }
    return (0);
}