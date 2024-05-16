#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>
#define EATING "%ld %ld is eating\n"
#define SLEEPING "%ld %ld is sleeping\n"
#define Thinking "%ld %ld is thinking\n"
#define DEAD "%ld %ld is dead\n"
#define TAKE "%ld %ld has taken a fork\n"

typedef struct s_table t_table;

typedef struct s_fork
{
	int	fork_id;
	pthread_mutex_t fork;
}	t_fork;

typedef struct s_philo
{
	long		id;
	long		meal_count;
	long		last_meal;
	bool		full;
	bool		is_eating;
	t_fork		*fork1;
	t_fork		*fork2;
	pthread_t 	philo;
	pthread_mutex_t	philo_mtx;
	t_table		*table;
}	t_philo;

struct s_table
{
	long 		philo_count;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	long		max_meals;
	long		start_time;
	long		full_count;
	long		running_threads;
	t_fork		*forks;
	t_philo 	*philos;
	bool		death;
	bool		ready;
	pthread_t	monitor;
	pthread_mutex_t	table_mtx;
};

// utils.c
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	wait_all_threads(t_table *table);
long	get_time(void);
void	print_msg(const char *str, t_philo *philo);
// init_data2.c
int init_mtx(t_table *table);
// free.c
void	free_forks(t_table *table);
void 	free_table_bs(t_table *table);
// init_data.c
int	init_data(t_table *table);
//parser.c
int parse_input(t_table *table, char **argv);
// set_and_get.c
void    set_bool(bool *var, bool value, pthread_mutex_t *mtx);
bool    get_bool(bool var, pthread_mutex_t *mtx);
void    set_long(long *var, long value, pthread_mutex_t *mtx);
long    get_long(long var, pthread_mutex_t *mtx);
bool    is_over(bool var, pthread_mutex_t *mtx);
// dinner.c
int start_dinner(t_table *table);
//eat.c
void    eat(t_philo *philo);
void    increase_long(long *var, pthread_mutex_t *mtx);
//monitor.c
void *monitor(void *arg);
#endif