#include "philosophers.h"

void	pickup_fork(t_philosopher *philo, int flag)
{
	if (flag == LEFT_FORK)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		printaction(" has taken a fork\n", philo);
		philo->left_fork = 1;
		if (ready2eat(philo))
			return ;
		else
			pickup_fork(philo, RIGHT_FORK);
	}
	if (flag == RIGHT_FORK)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->philos_total]);
		printaction(" has taken a fork\n", philo);
		philo->right_fork = 1;
		if (ready2eat(philo))
			return ;
		else
			pickup_fork(philo, LEFT_FORK);
	}
}