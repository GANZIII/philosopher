#include "./include/philosopher.h"

int	main(int argc, char *argv[])
{
	t_argset	arg;
	t_philo		*philo;

	if (init(argc, argv))
		return (1);
	if (init_arg(&arg, argc, argv))
		return (1);
	if (init_philo(&philo, &arg))
		return (1);
	threading(philo, &arg);
	dobby_philo(philo, arg.num_philo);
	dobby_fork(&arg, arg.num_philo);
	pthread_mutex_destroy(&arg.flag_mutex);
	pthread_mutex_destroy(&(arg.display_mutex));
	pthread_mutex_destroy(&arg.fin_eat_mutex);
	return (0);
}
