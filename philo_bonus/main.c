#include "head.h"

void	*ft_watching(void *parm)
{
	t_id	*id;
	int		x;

	x = 0;
	id = (t_id *)parm;
	while (1)
	{
		if (ft_time() - id->age >= id->data->td)
		{
			ft_state('d', id);
			exit(0);
		}
		if (id->done == id->data->t && x == 0)
			exit(1);
		usleep(100);
	}
	return (NULL);
}

int	ft_routing(t_id	*id)
{
	int			i;
	pthread_t	watch;

	i = id->index + 1;
	id->data->start = ft_time();
	if (i % 2)
		usleep(300);
	pthread_create(&watch, NULL, ft_watching, id);
	while (1)
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

void	ft_kill(t_data *data)
{
	int	i;
	int	*pid;

	pid = data->pids;
	i = 0;
	while (i < data->np)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}

void	ft_manage(t_data *data)
{
	int		pid;
	int		i;
	t_id	*id;
	int		status;

	i = 0;
	id = malloc(sizeof(t_id) * data->np);
	while (i < data->np)
	{
		pid = fork();
		if (pid == 0)
		{
			id[i].done = 0;
			id[i].data = data;
			id[i].index = i;
			id[i].age = ft_time();
			ft_routing(&id[i]);
		}
		else
			data->pids[i] = pid;
		i++;
	}
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 0)
		ft_kill(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!ft_check(ac, av, &data))
		return (0);
	data.pids = malloc(sizeof(int) * data.np);
	sem_unlink("forks");
	sem_unlink("f_meal");
	data.forks = sem_open("forks", O_CREAT, 0644, data.np);
	data.f_meal = sem_open("f_meal", O_CREAT, 0644, data.np);
	ft_manage(&data);
	sem_unlink("forks");
	sem_unlink("f_meal");
}
