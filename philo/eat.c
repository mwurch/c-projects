#include "philo.h"

void    pick_up_forks(t_philo *philo);
void    put_down_forks(t_philo *philo);
void    increase_long(long *var, pthread_mutex_t *mtx);

long    calc_starvation(t_philo *philo)
{
    long    current_time;
    long    time_since_last_meal;

    current_time = get_time();
    time_since_last_meal = current_time - philo->last_meal;

    if (time_since_last_meal >= (philo->table->time_to_die / 2))
        return (2);
    else
        return (1);
}

void    eat(t_philo *philo)
{
    if (calc_starvation(philo) == 1 && philo->last_meal != philo->table->start_time)
        usleep(20000);
    if (philo->last_meal == philo->table->start_time && philo->id % 2 == 0)
    {
        increase_long(&philo->last_meal, &philo->philo_mtx);
        return ;
    }
    pick_up_forks(philo);
    print_msg(EATING, philo);
    set_long(&philo->last_meal, get_time(), &philo->philo_mtx);
    usleep(philo->table->time_to_eat * 1000);
    put_down_forks(philo);
    philo->meal_count++;
    if (philo->table->max_meals > 0 && philo->meal_count >= philo->table->max_meals)
    {
        set_bool(&philo->full, true, &philo->philo_mtx);
        increase_long(&philo->table->full_count, &philo->table->table_mtx);
    }
    print_msg(SLEEPING, philo);
    usleep(philo->table->time_to_sleep * 1000);
}

void    pick_up_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork1->fork);
    print_msg(TAKE, philo);
    pthread_mutex_lock(&philo->fork2->fork);
    print_msg(TAKE, philo);
}

void    put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->fork2->fork);
    pthread_mutex_unlock(&philo->fork1->fork);
}

void    increase_long(long *var, pthread_mutex_t *mtx)
{
    pthread_mutex_lock(mtx);
    (*var)++;
    pthread_mutex_unlock(mtx);
}