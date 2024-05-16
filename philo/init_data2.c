#include "philo.h"

int init_mtx(t_table *table)
{
    if (pthread_mutex_init(&table->table_mtx, NULL) != 0)
        return (0);
    return (1);
}