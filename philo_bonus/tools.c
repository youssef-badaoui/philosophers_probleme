#include "head.h"

void	ft_state(int c, t_id *id)
{
	long long	e;

	e = ft_time() - id->data->start;
	if (c == 'e')
		printf("%lld %d is eating\n", e, id->index + 1);
	else if (c == 'f')
		printf("%lld %d has taken a fork\n", e, id->index + 1);
	else if (c == 's')
		printf("%lld %d is sleeping\n", e, id->index + 1);
	else if (c == 't')
		printf("%lld %d is thinking\n", e, id->index + 1);
	else if (c == 'd')
	{
		printf("%lld %d died\n", e, id->index + 1);
		return ;
	}
}

int	ft_isd(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long long	ft_time(void)
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
		nb = (nb * 10) + (str[i++] - 48);
	return (nb * j);
}

void	ft_usleep(long long time)
{
	long long	half;
	long long	start;
	long long	now;

	start = ft_time();
	half = time * (9 / 10);
	usleep(half * 1000);
	now = ft_time();
	while (now - start < time)
	{
		now = ft_time();
		usleep (100);		
	}
}

int	ft_check(int ac, char **av, t_data *data)
{
	if(!ft_isd(av))
		return (0);
	if (ac >= 5)
	{
		data->np = ft_atoi(av[1]);
		data->td = ft_atoi(av[2]);
		data->te = ft_atoi(av[3]);
		data->ts = ft_atoi(av[4]);
	}
	else 
		return (0);
	if (ac == 6)
		data->t = ft_atoi(av[5]);
	else
		data->t = -1;
	return (1);
}
