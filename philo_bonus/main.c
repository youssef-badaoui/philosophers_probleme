#include "head.h"

int main(int ac, char **av)
{
    t_data  data;

    if(!ft_check(ac, av, &data))
		  return (0);
    data.pids = malloc(sizeof(int)*data.np);
    ft_manage(&data);
}
