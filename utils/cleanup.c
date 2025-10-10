#include "philosophers.h"

int	cleanup(t_philosopher *philo, t_data *data, int flag, char *msg)
{
	size_t iter;

	iter = 0;
	while (data->forks && iter < data->philos_total)
	{
		pthread_mutex_destroy(&data->forks[iter]);
		iter++;
	}
	if (data->forks)
		free(data->forks);
	if (philo)
		free(philo);
	if (msg != NULL)
		write(2, msg, ft_strlen(msg));
	if (flag == FAILURE)
		return (1);
	if (flag == SUCCESS)
		return (0);
	return (0);
}