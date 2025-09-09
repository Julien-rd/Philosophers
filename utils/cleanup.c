#include "philosophers.h"

void cleanup(t_philosopher *philo, int flag, char *msg)
{
    if (philo)
        free(philo);
    if (philo->data->forks)
        free(philo->data->forks);
    if (msg != NULL)
        printf("%s\n", msg);
    if (flag == FAILURE)
        exit(1);
    if (flag == SUCCESS)
        exit(0);
}  