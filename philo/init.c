/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:52:20 by jijoo             #+#    #+#             */
/*   Updated: 2023/01/04 14:49:47 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosopher.h"

int init(int count, char **value)
{
    int idx;
    int jdx;

    idx = 1;
    if ((count != 5) && (count != 6))
        return (1);
    while (idx < count)
    {
        jdx = 0;
        while (value[idx][jdx])
            if (!ft_isdigit(value[idx][jdx++]))
                return (1);
        idx++;
    }
    return (0);
}

int init_mutex(t_argset *arg)
{
    int idx;

    idx = 0;
    if (pthread_mutex_init(&(arg->display_mutex), 0))
        return (1);
    arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
    if (!(arg->fork))
    {
        pthread_mutex_destroy(&(arg->display_mutex));
        return (1);
    }
    while (idx < arg->num_philo)
    {
        pthread_mutex_init(&(arg->fork[idx]), 0);
        idx++;
    }
    pthread_mutex_init(&arg->flag_mutex, 0);
    pthread_mutex_init(&arg->fin_eat_mutex, 0);
    return (0);
}

int init_arg(t_argset *arg, int argc, char *argv[])
{   
    arg->num_philo = ft_atoi(argv[1]);
    arg->time_to_die = ft_atoi(argv[2]);
    arg->time_to_eat = ft_atoi(argv[3]);
    arg->time_to_sleap = ft_atoi(argv[4]);
    arg->initial_time = get_time();
    arg->option = -1;
    arg->is_fin = 0;
    arg->fin_eat = 0;
    if (argc == 6)
    {
        arg->option = ft_atoi(argv[5]);
        if (arg->option <= 0)
            return (1);
    }
    if (arg->num_philo <= 0 || arg->time_to_die < 0 || arg->time_to_eat < 0 \
        || arg->time_to_sleap < 0)
        return (1);
    if (init_mutex(arg))
        return (1);
    return (0);
}

int init_philo(t_philo **philo, t_argset *arg)
{
    int idx;

    idx = 0;
    *philo = malloc(sizeof(t_philo) * arg->num_philo);
    if (!(*philo))
        return (1);
    while (idx < arg->num_philo)
    {
        (*philo)[idx].arg = arg;
        (*philo)[idx].id = idx;
        (*philo)[idx].fork_left = idx;
        (*philo)[idx].fork_right = (idx + 1) % arg->num_philo;
        (*philo)[idx].last_meal = get_time();
        (*philo)[idx].cnt_eat = 0;
        pthread_mutex_init(&(*philo)[idx].last_meal_mutex, 0);
        pthread_mutex_init(&(*philo)[idx].cnt_eat_mutex, 0);
        idx++;
    }
    return (0);
}