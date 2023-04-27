/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdamoha <abdamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:24:37 by abdamoha          #+#    #+#             */
/*   Updated: 2023/04/27 13:46:23 by abdamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *t)
{
	t_thread	*p = (t_thread *)t;
	while (1)
	{
		// if (everytime_check(p->f) == 1)
		// 	return (0);
		p->f->current = ft_gettime();
		if (check_for_forks(p->f, p->index) == 1)
		{
			// printf("index ");
			if (everytime_check(p->f) == 1)
				return (0);
			// pthread_mutex_lock(&p->f->mu);
			if (everytime_check(p->f) == 1)
			{
				return_forks(p->f, p->index);
				pthread_mutex_unlock(&p->f->mu);
				return (0);
			}
			taking_forks(p->f, p->index);
			// pthread_mutex_unlock(&p->f->mu);
			if (took_fork(p, p->index, p->f->current) == 1)
			{
				return_forks(p->f, p->index);
				p->f->status[p->index - 1] = -1;
				return (0);
			}
			eating(p, p->index, p->f->current);
			// if (everytime_check(p->f) == 1)
			// 	return (0);
			sleeping(p, p->index, p->f->current);
			thinking(p, p->index, p->f->current);
			// if (everytime_check(p->f) == 1)
			// 	return (0);
		}
		// pthread_mutex_unlock(&p->f->mutex);
		// if (p->f->current - p->last_eating >= p->d_t)
		// {
		// 	died(p, p->index, p->f->current);
		// 	exit(0);
		// }
		// if (check_if_died(p) == 1)
		// 	return (0);
		// j++;
		// sleep(1);
	}
	// if (everytime_check(p->f) == 1)
	// 	return (0);
	return (0);
}

void	eating(t_thread *p, int index, long long time)
{
	long long	b;

	(void)time;
	b = ft_gettime();
	p->last_eating = p->f->current;
	pthread_mutex_lock(&p->f->mu);
	printf("\033[0;32m[%lld] %d is eating\n", b - p->start_t, index);
	pthread_mutex_unlock(&p->f->mu);
	ft_usleep(p, p->e_t);
	// pthread_mutex_lock(&p->f->mu);
	return_forks(p->f, p->index);
	// pthread_mutex_unlock(&p->f->mu);
	gettimeofday(&p->tv, NULL);
	p->f->current = p->tv.tv_sec * 1000;
	p->f->current += p->tv.tv_usec / 1000;
	if (everytime_check(p->f) == 1)
		return ;
}

void	sleeping(t_thread *p, int index, long long time)
{
	long long	b;

	(void)time;
	b = ft_gettime();
	pthread_mutex_lock(&p->f->mu);
	printf("\033[0;36m[%lld] %d is sleeping\n", b - p->start_t, index);
	pthread_mutex_unlock(&p->f->mu);
	ft_usleep(p, p->sl_t);
	b = ft_gettime();
	if (everytime_check(p->f) == 1)
		return ;
	// pthread_mutex_unlock(&p->f->mu);
}

void	thinking(t_thread *p, int index, long long time)
{
	long long	b;

	(void)time;
	b = ft_gettime();
	if (everytime_check(p->f) == 1)
		return ;
	pthread_mutex_lock(&p->f->mu);
	printf("\033[0;35m[%lld] %d is thinking\n", b - p->start_t, index);
	pthread_mutex_unlock(&p->f->mu);
}

int	took_fork(t_thread *p, int index, long long time)
{
	long long	b;

	(void)time;
	b = ft_gettime();
	pthread_mutex_lock(&p->f->mu);
	printf("\033[0;34m[%lld] %d has taken the fork\n", b - p->start_t, index);
	pthread_mutex_unlock(&p->f->mu);
	if (check_if_died(p) == 1)
	{
		p->died = 1;
		// died(p, p->index, p->f->current);
		return (1);
	}
	if (everytime_check(p->f) == 1)
		return (0);
	return (0);
}

void	died(t_thread *p, int index, long long time)
{
	long long	b;

	(void)time;
	b = ft_gettime();
	pthread_mutex_lock(&p->f->mu);
	printf("\033[0;31m[%lld] %d died\n", b - p->start_t, index);
	pthread_mutex_unlock(&p->f->mu);
	// gettimeofday(&p->tv, NULL);
	// p->f->current = p->tv.tv_sec * 1000;
	// p->f->current += p->tv.tv_usec / 1000;
	// pthread_mutex_lock(&p->f->mu);
	// p->f->status[index] = -1;
	// pthread_mutex_unlock(&p->f->mu);
}
