#include "philo.h"

void	free_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&(table->forks[i].fork));
	free(table->forks);
}

void free_table_bs(t_table *table)
{
	free_forks(table);
	free(table->philos);
	free(table);
}