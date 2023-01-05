#include "./include/philosopher.h"

void	philo_fin2(t_argset *arg, t_philo *philo)
{
	int			idx;
	long int	now;

	pthread_mutex_unlock(&arg->fin_eat_mutex);
	idx = 0;
	while (idx < arg->num_philo)
	{
		now = get_time();
		pthread_mutex_lock(&philo[idx].last_meal_mutex);
		if ((now - philo[idx].last_meal) >= arg->time_to_die)
		{
			pthread_mutex_unlock(&philo[idx].last_meal_mutex);
			display(arg, "is died", idx);
			return ;
		}
		pthread_mutex_unlock(&philo[idx].last_meal_mutex);
		idx++;
	}
}

void	philo_fin(t_argset *arg, t_philo *philo)
{
	while (!check_update(arg, CHECK))
	{
		pthread_mutex_lock(&arg->fin_eat_mutex);
		if (arg->num_philo == arg->fin_eat)
		{
			pthread_mutex_unlock(&arg->fin_eat_mutex);
			check_update(arg, UPDATE);
		}
		else
			philo_fin2(arg, philo);
	}
}

void	*invoking(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->id % 2 == 0)
		ft_usleep(philo->arg->time_to_eat / 10);
	while (!check_update(philo->arg, CHECK))
	{
		philo_eat(philo->arg, philo);
		pthread_mutex_lock(&philo->cnt_eat_mutex);
		if (philo->arg->option == philo->cnt_eat)
		{
			pthread_mutex_unlock(&philo->cnt_eat_mutex);
			pthread_mutex_lock(&philo->arg->fin_eat_mutex);
			philo->arg->fin_eat += 1;
			pthread_mutex_unlock(&philo->arg->fin_eat_mutex);
			return (0);
		}
		else
			pthread_mutex_unlock(&philo->cnt_eat_mutex);
		philo_sleep(philo->arg, philo);
		display(philo->arg, "is thinking", philo->id);
	}
	return (0);
}

int	threading(t_philo *philo, t_argset *arg)
{
	int	idx;

	idx = 0;
	while (idx < arg->num_philo)
	{
		pthread_mutex_lock(&philo[idx].last_meal_mutex);
		philo[idx].last_meal = get_time();
		pthread_mutex_unlock(&philo[idx].last_meal_mutex);
		pthread_create(&(philo[idx].thread), 0, invoking, &(philo[idx]));
		idx++;
	}
	philo_fin(arg, philo);
	return (0);
}
