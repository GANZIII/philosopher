#include "./include/philosopher.h"

void	philo_eat(t_argset *arg, t_philo *philo)
{
	pthread_mutex_lock(&(arg->fork[(philo->fork_left)]));
	display(arg, "has taken a fork", philo->id);
	if (arg->num_philo > 1)
	{
		pthread_mutex_lock(&(arg->fork[philo->fork_right]));
		display(arg, "has taken a fork", philo->id);
		display(arg, "is eating", philo->id);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_lock(&philo->cnt_eat_mutex);
		philo->cnt_eat += 1;
		pthread_mutex_unlock(&philo->cnt_eat_mutex);
		ft_wait(arg->time_to_eat);
		pthread_mutex_unlock(&(arg->fork[philo->fork_right]));
	}
	pthread_mutex_unlock(&(arg->fork[philo->fork_left]));
}

void	philo_sleep(t_argset *arg, t_philo *philo)
{
	display(arg, "is sleeping", philo->id);
	ft_wait(arg->time_to_sleap);
}
