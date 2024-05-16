#include "philo.h"

// ./philo 5 300 100 100 [5]
int main(int argc, char **argv)
{
    t_table *table;

    if (argc == 5 || argc == 6)
    {
        table = calloc(sizeof(t_table), 1);// need_ft_calloc
        if (!parse_input(table, argv))
            return (-1);
        if (init_data(table) == -1)
            return (-1);
        start_dinner(table);
    }
    else
    {
        ft_putstr_fd("\033[31mWrong Input: Allowed Input: ./philo 5 300 100 100 [5]\n\033[0m", 2);
        return (-1);
    }
    return (0);
}