#include "philosophers.h"

int	protected_pthread_create(t_philosopher *philo, t_data *data, int pos)
{
	if (pthread_create(&philo[pos].newthread, NULL, routine,
			(int *)&philo[pos]) < 0)
		return (cleanup(philo, data, FAILURE, "PTHREAD_CREATE FAILED"));
	return (0);
}

int	protected_pthread_mutex_init(pthread_mutex_t *mutex, t_data *data,
		t_philosopher *philo)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (cleanup(philo, data, FAILURE, "PTHREAD_MUTEX_INIT FAILED"));
	return (0);
}
