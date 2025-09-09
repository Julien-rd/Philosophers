#include "philosophers.h"

void pickup_left_fork(t_philosopher *philo)
{

    protected_pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->number_of_philosophers - 1], NULL);
    philo->left_fork = 1;
    if ready2eat(philo)
        eat(philo);
    else
        pickup_right_fork(philo);
}