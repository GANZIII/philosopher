/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:39:01 by jijoo             #+#    #+#             */
/*   Updated: 2023/01/04 14:50:09 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosopher.h"

void    display(t_argset *arg, char *str, int id)
{
    long int    now;

    now = get_time();
    pthread_mutex_lock(&(arg->display_mutex));
    if (!(arg->is_fin))
        printf("%ld %d %s\n", now - arg->initial_time, id + 1, str);
    pthread_mutex_unlock(&(arg->display_mutex));
}

void    ft_wait(long int ms)
{
    long int    start;

    start = get_time();
    while ((get_time() - start) < ms)
        usleep(ms / 10);
}

void    dobby_fork(t_argset *arg, int idx)
{
    int i;

    i = 0;
    while (i < idx)
    {
        pthread_mutex_unlock(&(arg->fork[i]));
        pthread_mutex_destroy(&(arg->fork[i]));
        i++;
    }
    free(arg->fork);
}

void    dobby_philo(t_philo *philo, int idx)
{
    int i;

    i = 0;
    while (i < idx)
    {
        pthread_mutex_destroy(&philo->last_meal_mutex);
        pthread_mutex_destroy(&philo->cnt_eat_mutex);
        pthread_join(philo[i].thread, 0);
        i++;
    }
    free(philo);
}