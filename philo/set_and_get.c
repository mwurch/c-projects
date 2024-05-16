#include "philo.h"

void    set_bool(bool *var, bool value, pthread_mutex_t *mtx);
bool    get_bool(bool var, pthread_mutex_t *mtx);
void    set_long(long *var, long value, pthread_mutex_t *mtx);
long    get_long(long var, pthread_mutex_t *mtx);
bool    is_over(bool var, pthread_mutex_t *mtx);

bool    is_over(bool var, pthread_mutex_t *mtx)
{
    bool    res;

    pthread_mutex_lock(mtx);
    res = var;
    pthread_mutex_unlock(mtx);
    return (res);
}

void    set_bool(bool *var, bool value, pthread_mutex_t *mtx)
{
    pthread_mutex_lock(mtx);
    *var = value;
    pthread_mutex_unlock(mtx);
}

bool    get_bool(bool var, pthread_mutex_t *mtx)
{
    bool    ret;

    pthread_mutex_lock(mtx);
    ret = var;
    pthread_mutex_unlock(mtx);
    return (ret);
}

void    set_long(long *var, long value, pthread_mutex_t *mtx)
{
    pthread_mutex_lock(mtx);
    *var = value;
    pthread_mutex_unlock(mtx);
}

long    get_long(long var, pthread_mutex_t *mtx)
{
    long    ret;

    pthread_mutex_lock(mtx);
    ret = var;
    pthread_mutex_unlock(mtx);
    return (ret);
}
