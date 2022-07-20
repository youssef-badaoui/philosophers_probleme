/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybadaoui <ybadaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:21:56 by ybadaoui          #+#    #+#             */
/*   Updated: 2022/07/19 19:50:25 by ybadaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_bonus.h"

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
