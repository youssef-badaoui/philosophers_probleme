#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>


typedef struct s_data {
	int np;
	int te;
	int ts;
	int td;
	int t;
	long long start;
	pid_t *pids;
	sem_t *forks;
	sem_t *f_meal;
} t_data;

typedef struct s_id
{
	int index;
	long long age;
	int done;
	t_data *data;
} t_id;

void    ft_manage(t_data *data);

long	long ft_time();
int		ft_atoi(const char *str);
void	ft_usleep(long long time);
void	ft_state(int c, t_id *id);
int		ft_death(t_id *id);
void	*srv(void *parm);
int		ft_check(int ac, char **av, t_data *data);
#endif