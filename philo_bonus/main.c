#include "head.h"

int main(int ac, char **av)
{
    t_data  data;

    if(!ft_check(ac, av, &data))
		  return (0);
    data.pids = malloc(sizeof(int)*data.np);
    sem_unlink("forks");
    sem_unlink("f_meal");
    data.forks = sem_open("forks", O_CREAT, 0644, data.np);
    data.f_meal = sem_open("f_meal", O_CREAT, 0644, data.np);
    ft_manage(&data);
}

