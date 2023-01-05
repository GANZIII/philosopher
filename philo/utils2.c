#include "./include/philosopher.h"

void	display(t_argset *arg, char *str, int id)
{
	long int	now;

	now = get_time();
	pthread_mutex_lock(&(arg->display_mutex));
	if (!check_update(arg, CHECK))
		printf("%ld %d %s\n", now - arg->initial_time, id + 1, str);
	if (!ft_strncmp(str, "is died", 7))
	{
		check_update(arg, UPDATE);
	}
	pthread_mutex_unlock(&(arg->display_mutex));
}

void	ft_wait(long int ms)
{
	long int	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(ms / 10);
}

void	dobby_fork(t_argset *arg, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		pthread_mutex_unlock(&(arg->fork[i]));
		pthread_mutex_destroy(&(arg->fork[i]));
		i++;
	}
	free(arg->fork);
}

void	dobby_philo(t_philo *philo, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		pthread_join(philo[i].thread, 0);
		pthread_mutex_destroy(&philo->last_meal_mutex);
		pthread_mutex_destroy(&philo->cnt_eat_mutex);
		i++;
	}
	free(philo);
}
