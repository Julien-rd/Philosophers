#include "philosophers.h"

int	protected_pthread_create(t_philosopher *philo, t_data *data, int pos)
{
	if (pthread_create(&philo[pos].newthread, NULL, routine,
			(int *)&philo[pos]) < 0)
		return (cleanup(philo, data, FAILURE, "PTHREAD_CREATE FAILED"));
	return (0);
}
