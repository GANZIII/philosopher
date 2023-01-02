/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:37:01 by jijoo             #+#    #+#             */
/*   Updated: 2023/01/02 16:35:34 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosopher.h"

void    philo_eat(t_argset *arg, t_philo *philo)
{
    pthread_mutex_lock(&(arg->fork[(philo->fork_left)]));
    display(arg, "has taken a fork", philo->id);
    if (arg->num_philo > 1)
    {
        pthread_mutex_lock(&(arg->fork[philo->fork_right]));
        display(arg, "has taken a fork", philo->id);
        display(arg, "is eating", philo->id);
        philo->last_meal = get_time();
        philo->cnt_eat += 1;
        ft_wait(arg->time_to_eat);
        pthread_mutex_unlock(&(arg->fork[philo->fork_right]));
    }
    pthread_mutex_unlock(&(arg->fork[philo->fork_left]));
}

void    philo_sleep(t_argset *arg, t_philo *philo)
{
    display(arg, "is sleeping", philo->id);
    ft_wait(arg->time_to_sleap);
}