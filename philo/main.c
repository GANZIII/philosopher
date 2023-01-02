/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:37:32 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/31 16:52:45 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philosopher.h"

int main(int argc, char *argv[])
{
    t_argset    arg;
    t_philo     *philo;
    
    if (init(argc, argv))
        return (1);
    if (init_arg(&arg, argc, argv))
        return (1);
    if (init_philo(&philo, &arg))
        return (1);
    if (threading(philo, &arg))
        return (1);
    pthread_mutex_destroy(&(arg.display_mutex));
    dobby_fork(&arg, arg.num_philo);
    dobby_philo(philo, arg.num_philo);
    return (0);
}