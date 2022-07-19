/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:22:08 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/07/19 16:35:37 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>

typedef struct s_data {
	int				np;
	int				te;
	int				ts;
	int				td;
	int				t;
	long long		start;
	pthread_mutex_t	aff;
}	t_data;

typedef struct s_id
{
	int				index;
	long long		age;
	int				done;
	t_data			*data;
	pthread_mutex_t	*forks;
}	t_id;

long long	ft_time(void);
int			ft_atoi(const char *str);
void		ft_usleep(long long time);
void		ft_state(int c, t_id *id);
int			ft_death(t_id *id);
void		*srv(void *parm);
int			ft_check(int ac, char **av, t_data *data);
#endif