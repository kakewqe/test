#include "../inc/philo.h"

void	write_status(char *str, t_philo *ph)
{
	long int		time;

	time = -1;
	time = get_time() - ph->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status(SLEEP, ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->sleep);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status(THINK, ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void activity(t_philo *ph)
{
    pthread_mutex_lock(&ph->l_f);
    pthread_mutex_lock(&ph->pa->write_mutex);
    write_status(TAKE_F, ph);
    if (!ph->r_f)
    {
        pthread_mutex_unlock(&ph->pa->write_mutex);
        pthread_mutex_unlock(&ph->l_f);
        ft_usleep(ph->pa->die * 2);
        return;
    }
    pthread_mutex_lock(ph->r_f); // Assurez-vous que ph->r_f est un pointeur de verrou
    pthread_mutex_unlock(&ph->pa->write_mutex); // Déverrouillez avant d'entrer dans la section critique suivante
    pthread_mutex_lock(&ph->pa->write_mutex);
    write_status(TAKE_F, ph);
    write_status(EAT, ph);
    pthread_mutex_unlock(&ph->pa->write_mutex);
    pthread_mutex_lock(&ph->pa->time_eat);
    ph->ms_eat = get_time();
    pthread_mutex_unlock(&ph->pa->time_eat);
    ft_usleep(ph->pa->eat);
    pthread_mutex_unlock(ph->r_f);
    pthread_mutex_unlock(&ph->l_f);
    sleep_think(ph);
}
