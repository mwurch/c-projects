#include "philo.h"

void    *dinner(void* data)
{
    t_philo *philo;

    philo = (t_philo *) data;
    set_long(&philo->last_meal, get_time(), &philo->philo_mtx);
    wait_all_threads(philo->table);
    increase_long(&philo->table->running_threads, &philo->table->table_mtx);
    while (!is_over(philo->table->death, &philo->table->table_mtx) && !get_bool(philo->full, &philo->philo_mtx))
    {
        eat(philo);
        print_msg(Thinking, philo);
        usleep(1000);
    }
    return (NULL);
}
int start_dinner(t_table *table)
{
    int i;
    void * arg;

    i = -1;
    while (++i < table->philo_count)
    {
        arg = (void *) &table->philos[i];
        pthread_create(&table->philos[i].philo, NULL, dinner, arg);
    }
    arg = (void *) table;
    i = -1;
    table->start_time = get_time();
    pthread_create(&table->monitor, NULL, monitor, arg);
    set_bool(&table->ready, true, &table->table_mtx);
    while (++i < table->philo_count)
        pthread_join(table->philos[i].philo, NULL);
    pthread_join(table->monitor, NULL);
    return (1);
}