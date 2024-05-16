#include "philo.h"

static int	init_forks(t_table *table, int id)
{
	int	i;

	i = -1;
	table->forks[id].fork_id = id;
	if (pthread_mutex_init(&(table->forks[id].fork), NULL) != 0)
	{
		while (++i < id)
			pthread_mutex_destroy(&(table->forks[i].fork));
		free(table->forks);
		return (-1);
	}
	return (0);
}

static void	set_up_forks(t_fork * forks, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->fork1 = &forks[philo->id % philo->table->philo_count];
		philo->fork2 = &forks[philo->id - 1];
	}
	else
	{
		philo->fork1 = &forks[philo->id - 1];
		philo->fork2 = &forks[philo->id % philo->table->philo_count];
	}
}

static int	init_philo(t_table *table)
{
	t_philo	*philo;
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
	{
		free_forks(table);
		return (-1);
	}
	while (++i < table->philo_count)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->table = table;
		philo->full = false;
		philo->is_eating = false;
		philo->meal_count = 0;
		pthread_mutex_init(&philo->philo_mtx, NULL);
		set_up_forks(table->forks, philo);
	}
	return (0);
}

static int	init_philo_and_forks(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(t_fork) * table->philo_count);
	if (!table->forks)
		return (-1);
	while (++i < table->philo_count)
		if (init_forks(table, i) == -1)
			return (-1);
	if (init_philo(table) == -1)
		return (-1);

	return (0);
}

int	init_data(t_table *table)
{
	table->death = false;
	if (init_philo_and_forks(table) == -1)
	{
		free(table);
		return (-1);
	}
	if (!init_mtx(table))
	{
		free_table_bs(table);
		return (-1);
	}
	return (0);
}