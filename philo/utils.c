#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	wait_all_threads(t_table *table)
{
	while (!table->ready)
		;
}

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_msg(const char *str, t_philo *philo)
{
	if (!is_over(philo->table->death, &philo->table->table_mtx))
		printf(str, get_time() - philo->table->start_time, philo->id);
}