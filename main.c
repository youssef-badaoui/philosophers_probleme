#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>


typedef struct s_data {
	int np;
	int te;
	int ts;
	int td;
	int t;
	int start;
} t_data;

typedef struct s_id
{
	int index;
	int age;
	int done;
	t_data *data;
	pthread_mutex_t *forks;
} t_id;

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + 48);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 1;
	nb = 0;
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

int ft_death(t_id *id)
{
	int i;
	int t;

	i = 0;
	t = 0;
	while(1)
	{
		if(ft_time() - id[i].age > id->data->td)
			break;
		if(id[i].done == id->data->t)
			t++;
		if(t == id->data->np)
			break;
		i++;
		if(i == id->data->np)
			i = 0;
	}
	ft_state('d', i, id->data->start);
}

long long ft_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000);
}

void	ft_state(int c, int i, int t)
{
	struct timeval time;
	long long e;

	gettimeofday(&time, NULL);
	if(t == 0)
	{
		e = t - time.tv_sec * 1000;
		ft_putnbr(e);
		ft_putnbr(i);
		if(c == 'e')
			ft_putstr(" is eating\n");
		else if(c == 'f')
			ft_putstr(" has taken a fork\n");
		else if(c == 's')
			ft_putstr(" is sleeping\n");
		else if(c == 't')
			ft_putstr(" is thinking\n");
		else if(c == 'd')
			ft_putstr(" died\n");
		t = 0;
	}
}

void *srv(t_id *id)
{
	int i;
	long long t;
	int n;

	i = id[i].index;
	t = id->data->start;
	while(1)
	{
		pthread_mutex_lock(&id->forks[i]);
		ft_state('f', i, t);
		pthread_mutex_lock(&id->forks[(i + 1) % id->data->np]);
		ft_state('f', i, t);
		ft_state('e', i, t);
		id->age = ft_time();
		id->done++;
		usleep(id->data->te * 1000);
		pthread_mutex_unlock(&id->forks[i]);
		pthrtead_mutex_unlock(&id->forks[(i + 1) % id->data->np]);
		ft_state('s', i, t);
		sleep(id->data->ts * 1000);
		ft_state('t', i, t);
	}
}

int main(int ac, char **av)
{
	int i;

	t_id id[ft_atoi(av[1])];
	pthread_t philo[ft_atoi(av[1])];
	pthread_mutex_t fork[ft_atoi(av[1])];

	id->forks = &fork;
	id->data->np =  ft_atoi(av[1]);
	id->data->td = ft_atoi(av[2]);
	id->data->te = ft_atoi(av[3]);
	id->data->ts = ft_atoi(av[4]);
	id->data->t = ft_atoi(av[5]);
	i = 0;
	while(i < id->data->np)
		pthread_mutex_init(&id->forks[i], NULL);
	i = 0;
	while (i < id->data->np)
	{
		id->index = i + 1;
		id->age = ft_time();
		id->done = 0;
		id->data->start = ft_time();
		pthread_create(&philo[i], NULL, &srv, &id);
		pthread_detach(&philo[i]);
		i++;
	}
	ft_death(id);
}
