#include "philo.h"

static bool	is_space(int c)
{
	return ((c <= 13 && c >= 9) || c == 32);
}

static bool	is_num(int c)
{
	return (c <= '9' && c >= '0');
}

static long get_data(const char *str)
{
	long	ret;

	ret = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		ft_putstr_fd("Detected negativ number: Please use positiv numbers only!\n", 2);
		return (-2);
	}
	if (!is_num(*str))
	{
		ft_putstr_fd("Please use valid numbers!\n", 2);
		return (-2);
	}
	else
	{
		while (is_num(*str))
		{
			ret = ret * 10 + (*str - 48);
			str++;
		}
	}
	if (ret < 1 || INT_MAX < ret)
		return (-2);
	return (ret);
}

static bool check_data(t_table *table)
{
	return (!(table->philo_count == -2 ||
			table->time_to_die == -2 ||
			table->time_to_eat == -2 ||
			table->time_to_sleep == -2 ||
			table->max_meals == -2));
}

int parse_input(t_table *table, char **argv)
{
	table->philo_count = get_data(argv[1]);
	table->time_to_die = get_data(argv[2]);
	table->time_to_eat = get_data(argv[3]);
	table->time_to_sleep = get_data(argv[4]);
	if (argv[5])
		table->max_meals = get_data(argv[5]);
	else
		table->max_meals = -1;
	if (check_data(table) == false)
	{
		free(table);
		return (0);
	}
	table->ready = false;
	table->running_threads = 0;
	table->full_count = 0;
	table->death = false;
	return (1);
}