#include "philo/philosophers.h"

int main(int ac, char **av)
{
    t_data  data;

    if(!ft_check(ac, av, &data))
		return (0);
    ft_manage(&data);
}

