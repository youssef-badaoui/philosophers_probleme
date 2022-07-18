#include "head.h"
int	ft_routing(t_id	*id)
{
	int	i;

	i = id->index + 1;
	if(i % 2)
		usleep(300);
	while(1)
	{
		ft_state('t', id);
		
	}
}

void	ft_manage(t_data *data)
{
	int pid;
	int i;
	t_id *id;

	i = 0;
	id = malloc(sizeof(t_id)*data->np);
	while(i < data->np)
	{
		pid = fork();
		if (!pid)
		{
			ft_routing(id);
		}
		else
			data->pids[i] = pid;
	}
}