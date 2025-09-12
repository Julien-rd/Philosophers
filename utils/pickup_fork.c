#include "philosophers.h"

void	pickup_fork(t_philosopher *philo, int flag)
{
	if (flag == LEFT_FORK)
	{
		alive_check(philo, 0);
		protected_pthread_mutex_lock(&philo->data->forks[philo->id - 1], NULL);
		printaction("has taken a fork", philo);
		// alive_check(philo, philo->data->time_to_eat);
		philo->left_fork = 1;
		if (ready2eat(philo))
			return ;
		else
		{
			alive_check(philo, philo->data->time_to_eat);
			pickup_fork(philo, RIGHT_FORK);
		}
	}
	if (flag == RIGHT_FORK)
	{
		alive_check(philo, 0);
		// alive_check(philo, philo->data->time_to_eat);
		protected_pthread_mutex_lock(&philo->data->forks[philo->id
			% philo->data->number_of_philosophers], NULL);
		printaction("has taken a fork", philo);
		// alive_check(philo, philo->data->time_to_eat);
		philo->right_fork = 1;
		if (ready2eat(philo))
			return ;
		else
		{
			alive_check(philo, philo->data->time_to_eat);
			pickup_fork(philo, LEFT_FORK);
		}
	}
}