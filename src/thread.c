
#include "../inc/philo.h"


void *is_dead(void *data)
{
    t_philo *ph = (t_philo *)data;

    ft_usleep(ph->pa->die + 1);

    pthread_mutex_lock(&ph->pa->finish); // Verrou global
    if (!check_death(ph, 0) && !ph->finish && ((get_time() - ph->ms_eat) >= (long)(ph->pa->die)))
    {
        pthread_mutex_unlock(&ph->pa->finish); // Déverrouillage en cas de retour anticipé

        pthread_mutex_lock(&ph->pa->write_mutex); // Verrou pour l'écriture
        write_status(DEAD, ph);
        pthread_mutex_unlock(&ph->pa->write_mutex); // Déverrouillage après écriture

        check_death(ph, 1); // Marquer le philosophe comme mort
    }
    else
    {
        pthread_mutex_unlock(&ph->pa->finish); // Déverrouillage en cas de retour anticipé
    }

    return (NULL);
}


void *thread(void *data)
{
    t_philo *ph = (t_philo *)data;

    if (ph->id % 2 == 0)
        ft_usleep(ph->pa->eat / 10);

    pthread_create(&ph->thread_death_id, NULL, is_dead, data); // Création du thread à l'extérieur de la boucle
    pthread_detach(ph->thread_death_id); // Détachement du thread à l'extérieur de la boucle

    while (!check_death(ph, 0))
    {
        activity(ph);
        if ((int)++ph->nb_eat == ph->pa->m_eat)
        {
            pthread_mutex_lock(&ph->pa->finish);
            ph->finish = 1;
            ph->pa->nb_p_finish++;
            if (ph->pa->nb_p_finish == ph->pa->total)
            {
                pthread_mutex_unlock(&ph->pa->finish);
                check_death(ph, 2);
            }
            else
            {
                pthread_mutex_unlock(&ph->pa->finish);
            }
            return (NULL);
        }
    }

    return (NULL);
}
