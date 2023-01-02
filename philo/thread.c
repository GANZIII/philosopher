/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:54:48 by jijoo             #+#    #+#             */
/*   Updated: 2023/01/02 16:30:33 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosopher.h"

void    philo_fin(t_argset *arg, t_philo *philo)
{
    int         idx;
    long int    now;

    while (!(arg->is_fin))
    {
        if (arg->num_philo == arg->fin_eat)
            arg->is_fin = 1;
        else
        {
            idx = 0;
            while (idx < arg->num_philo)
            {
                now = get_time();
                if ((now - philo[idx].last_meal) >= arg->time_to_die)
                {
                    display(arg, "is died", idx);
                    arg->is_fin = 1;
                    break;
                }
                idx++;
            }
        }
    }
}

void    *invoking(void *param)
{
    t_philo     *philo;
    t_argset    *p_arg;

    philo = (t_philo *)param;
    p_arg = philo->arg;
    if (philo->id % 2 == 0)
		ft_usleep(p_arg->time_to_eat / 10);
    while (!p_arg->is_fin)
    {
        philo_eat(p_arg, philo);
        if (p_arg->option == philo->cnt_eat)
        {
            p_arg->fin_eat += 1;
            return (0);
        }
        philo_sleep(p_arg, philo);
        display(p_arg, "is thinking", philo->id);
        
    }   
    return (0);
}

int threading(t_philo *philo, t_argset *arg)
{
    int idx;

    idx = 0;
    while (idx < arg->num_philo)
    {
        philo[idx].last_meal = get_time();
        if (pthread_create(&(philo[idx].thread), 0, invoking, &(philo[idx])))
        {
            pthread_mutex_destroy(&(arg->display_mutex));
            dobby_philo(philo, idx);
            dobby_fork(arg, arg->num_philo);
            return (1);
        }
        idx++;
    }
    philo_fin(arg, philo);
    return (0);
}