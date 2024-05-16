#include "philo.h"


bool    is_dead(t_philo * philo)
{
    long    passed_time;

    if (get_bool(philo->full, &philo->philo_mtx))
        return (false);
    passed_time = get_time() - get_long(philo->last_meal, &philo->philo_mtx);
    if (passed_time >= philo->table->time_to_die)
        return (true);
    return (false);
}

void    all_threads_started(t_table *table)
{
    while (1)
    {
        if (get_long(table->running_threads, &table->table_mtx) >= table->philo_count)
            break ;
    }
}

void *monitor(void *arg)
{
    t_table *table;
    int i;

    table = (t_table *) arg;
   
    all_threads_started(table);
    while (!is_over(table->death, &table->table_mtx))
    {
        i = -1;
        if (table->philo_count == get_long(table->full_count, &table->table_mtx))
        {
            set_bool(&table->death, true, &table->table_mtx);
        }
        while (++i < table->philo_count)
        {
            if (is_dead(table->philos + i) && !is_over(table->death, &table->table_mtx))
            {
                set_bool(&table->death, true, &table->table_mtx);
                printf("%ld %ld is dead\n", get_time() - table->start_time, table->philos[i].id);
                break;
            }
        }
    }
    return (NULL);
}