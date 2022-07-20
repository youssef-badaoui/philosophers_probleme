/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:19:16 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/07/20 12:55:25 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_state(int c, t_id *id)
{
	long long	e;

	e = ft_time() - id->data->start;
	pthread_mutex_lock(&id->data->aff);
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
	pthread_mutex_unlock(&id->data->aff);
}

int	ft_death(t_id *id)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (1)
	{
		if (ft_time() - id[i].age >= id->data->td)
		{
			ft_state('d', &id[i]);
			break ;
		}
		if (id[i].done == id[i].data->t)
		{
			p++;
			id[i].done = 0;
		}
		if (p == id->data->np)
			break ;
		i++;
		if (i == id->data->np)
			i = 0;
		usleep (500);
	}
	return (0);
}

void	*srv(void *parm)
{
	int		i;
	t_id	*id;

	id = parm;
	i = id->index;
	if (i % 2 == 0)
		usleep(600);
	while (1)
	{
		ft_state('t', id);
		pthread_mutex_lock(&id->forks[i]);
		ft_state('f', id);
		pthread_mutex_lock(&id->forks[(i + 1) % id->data->np]);
		ft_state('f', id);
		id->age = ft_time();
		ft_state('e', id);
		ft_usleep(id->data->te);
		id->done++;
		pthread_mutex_unlock(&id->forks[i]);
		pthread_mutex_unlock(&id->forks[(i + 1) % id->data->np]);
		ft_state('s', id);
		ft_usleep(id->data->ts);
	}
	return (0);
}

void	ft_launch(t_id *id, t_data *data,
	pthread_mutex_t	*fork, pthread_t	*philo)
{
	int	i;

	i = 0;
	while (i < data->np)
	{
		id[i].data = data;
		id[i].forks = fork;
		id[i].index = i;
		id[i].done = 0;
		id[i].age = ft_time();
		id->data->start = ft_time();
		pthread_create(&philo[i], NULL, srv, &id[i]);
		pthread_detach(philo[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int					i;
	t_id				*id;
	pthread_t			*philo;
	pthread_mutex_t		*fork;
	t_data				data;

	id = malloc(sizeof(t_id) * ft_atoi(av[1]));
	philo = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!ft_check(ac, av, &data))
		return (0);
	if (data.t == 0)
		return (0);
	pthread_mutex_init(&data.aff, NULL);
	i = 0;
	while (i < data.np)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	ft_launch(id, &data, fork, philo);
	ft_death(id);
	free(id);
	free(philo);
	free(fork);
	return (0);
}
