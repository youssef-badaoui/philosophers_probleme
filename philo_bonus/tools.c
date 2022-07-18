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
		sem_wait(id->data->forks);
		ft_state('f', id);
		sem_wait(id->data->forks);
		ft_state('f', id);
		id->age = ft_time();
		ft_state('e', id);
		ft_usleep(id->data->te);
		id->done++;
		sem_post(id->data->forks);
		sem_post(id->data->forks);
		ft_state('s', id);
		ft_usleep(id->data->ts);
	}
}

void	ft_watch(t_id *id)
{
	while(1)
	{
		if(ft_time() - id->age >= id->data->td)
		{
			ft_state('d', id);
			break ;
		}
		usleep(100);
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
			id[i].done = 0;
			id[i].data = data;
			id[i].index = i;
			id[i].age = ft_time;
			ft_routing(id);
		}
		else
			data->pids[i] = pid;
		i++;
	}
	ft_watch(data);
}