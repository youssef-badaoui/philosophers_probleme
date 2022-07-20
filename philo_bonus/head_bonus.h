/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:48:27 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/07/20 12:49:17 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_BONUS_H
# define HEAD_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <time.h>
# include <stdlib.h>
# include <semaphore.h>

typedef struct s_data {
	int			np;
	int			te;
	int			ts;
	int			td;
	int			t;
	long long	start;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*f_meal;
}	t_data;

typedef struct s_id
{
	int			index;
	long long	age;
	int			done;
	t_data		*data;
}	t_id;

void		ft_manage(t_data *data);
long long	ft_time(void);
int			ft_atoi(const char *str);
void		ft_usleep(long long time);
void		ft_state(int c, t_id *id);
int			ft_death(t_id *id);
void		*srv(void *parm);
int			ft_check(int ac, char **av, t_data *data);
#endif