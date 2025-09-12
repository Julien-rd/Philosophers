#include "philosophers.h"

void	*protected_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		cleanup(NULL, FAILURE, "MALLOC FAILED!");
	return (ptr);
}

int	protected_pthread_create(t_philosopher *philo, int pos)
{
	if (pthread_create(&philo[pos].newthread, NULL, routine,
			(int *)&philo[pos]) < 0)
		return (cleanup(philo, FAILURE, "PTHREAD_CREATE FAILED"));
	return (0);
}

int	protected_pthread_join(t_philosopher *philo, int pos)
{
	if (pthread_join(philo[pos].newthread, NULL) < 0)
		return(cleanup(philo, FAILURE, "PTHREAD_JOIN FAILED"));
    return (0);
}

int	protected_pthread_mutex_init(pthread_mutex_t *mutex, t_philosopher *philo)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return(cleanup(philo, FAILURE, "PTHREAD_MUTEX_INIT FAILED"));
    return (0);
}

int	protected_pthread_mutex_lock(pthread_mutex_t *mutex, t_philosopher *philo)
{
	if (pthread_mutex_lock(mutex) != 0)
		return(cleanup(philo, FAILURE, "PTHREAD_MUTEX_LOCK FAILED"));
    return (0);
}

int	protected_pthread_mutex_unlock(pthread_mutex_t *mutex, t_philosopher *philo)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return(cleanup(philo, FAILURE, "PTHREAD_MUTEX_UNLOCK FAILED"));
    return (0);
}