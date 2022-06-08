#include "philosophers.h"

typedef struct s_data {
	int np;
	int te;
	int ts;
	int td;
	int t;
	long long start;
	pthread_mutex_t aff;
} t_data;

typedef struct s_id
{
	int index;
	long long age;
	int done;
	t_data *data;
	pthread_mutex_t *forks;
} t_id;


long long ft_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 1;
	nb = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		||str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 43)
			j = 1;
		else
			j = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (nb * j);
}

void	ft_usleep(long long time)
{
	long long	half;
	long long	start;
	long long	now;

	start = ft_time();
	half = time * (7/10);
	usleep(half * 1000);
	while (now - start < time)
	{
		now = ft_time();
		usleep (100);
	}
}

void	ft_state(int c, int i, t_id *id)
{
	long long	e;

	e = ft_time() - id->data->start;
	pthread_mutex_lock(&id->data->aff);
	if (c == 'e')
		printf("%lld %d is eating\n", e, i);
	else if (c == 'f')
		printf("%lld %d has taken a fork\n", e, i);
	else if (c == 's')
		printf("%lld %d is sleeping\n", e, i);
	else if (c == 't')
		printf("%lld %d is thinking\n", e, i);
	else if (c == 'd')
	{
		printf("%lld %d died\n", e, i);
		return ;
	}
	pthread_mutex_unlock(&id->data->aff);
}

int	ft_death(t_id *id)
{
	int i;
	int p;

	i = 0;
	p = 0;
	if(id->data->t == 0)
		return (0);
	while (1)
	{
		if (ft_time() - id[i].age >= id->data->td)
		{
			ft_state('d', i+1, id);
			break ;
		}
		if(id[i].done == id[i].data->t)
		{
			p++;
			id[i].done = 0;
		}
		if(p == id->data->np)
			break ;
		i++;
		if(i == id->data->np)
			i = 0;
		usleep (100);
	}
	return (0);
}

void *srv(void *parm)
{
	int i;
	int n;
	t_id *id;


	id = parm;
	i = id->index;
	if(i % 2)
		usleep(100);
	while(1)
	{
		ft_state('t', i, id);
		pthread_mutex_lock(&id->forks[i]);
		ft_state('f', i, id);
		if(id->data->np != 1)
			pthread_mutex_lock(&id->forks[(i + 1) % id->data->np]);
		else
			while(1);
		ft_state('f', i, id);
		ft_state('e', i, id);
		id->age = ft_time();
		ft_usleep(id->data->te);
		if(id->data->t)
			id->done++;
		pthread_mutex_unlock(&id->forks[i]);
		pthread_mutex_unlock(&id->forks[(i + 1) % id->data->np]);
		ft_state('s', i, id);
		ft_usleep(id->data->ts);
	}
	return 0;
}


int main(int ac, char **av)
{
	int	i;
	t_id			id[ft_atoi(av[1])];
	pthread_t		philo[ft_atoi(av[1])];
	pthread_mutex_t	fork[ft_atoi(av[1])];
	t_data			data;

	if(ac >= 5)
	{
		data.np = ft_atoi(av[1]);
		data.td = ft_atoi(av[2]);
		data.te = ft_atoi(av[3]);
		data.ts = ft_atoi(av[4]);
	}
	else return (0);
	if (ac == 6)
		data.t = ft_atoi(av[5]);
	else 
		data.t = -1;
	pthread_mutex_init(&data.aff, NULL);
	i = 0;
	while(i < data.np)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data.np)
	{
		id[i].data = &data;
		id[i].forks = fork;
		id->data->start = ft_time();
		id[i].index = i + 1;
		id[i].age = ft_time();
		id[i].done = 0;
		pthread_create(&philo[i], NULL, srv, &id[i]);
		pthread_detach(philo[i]);
		i++;
	}
	ft_death(id);
	return (0);
}