/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:34:50 by jijoo             #+#    #+#             */
/*   Updated: 2022/12/31 16:54:43 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_argset
{
    int             num_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleap;
    int             option;
    pthread_mutex_t display_mutex;
    pthread_mutex_t *fork;
    int             fin_eat;
    long int        initial_time;
    int             is_fin;
}   t_argset;

typedef struct s_philo
{
    int             id;
    long int        last_meal;
    int             cnt_eat;
    t_argset        *arg;
    pthread_t       thread;
    int             fork_right;
    int             fork_left;
}   t_philo;

// utils1.c
int     	ft_isdigit(int c);
int     	ft_atoi(const char *str);
long int    get_time(void);
void        ft_usleep(long int ms);

// utils2.c
void        display(t_argset *arg, char *str, int id);
void        ft_wait(long int ms);
void        dobby_fork(t_argset *arg, int idx);
void        dobby_philo(t_philo *philo, int idx);

// init.c
int         init(int count, char **value);
int         init_mutex(t_argset *arg);
int         init_arg(t_argset *arg, int argc, char *argv[]);
int         init_philo(t_philo **philo, t_argset *arg);

// thread.c
void        philo_fin(t_argset *arg, t_philo *philo);
void        *invoking(void *param);
int         threading(t_philo *philo, t_argset *arg);

// activity.c
void        philo_eat(t_argset *arg, t_philo *philo);
void        philo_sleep(t_argset *arg, t_philo *philo);
#endif