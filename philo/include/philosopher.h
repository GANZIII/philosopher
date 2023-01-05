#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define CHECK 1
# define UPDATE 2

typedef struct s_argset
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleap;
	int				option;
	pthread_mutex_t	display_mutex;
	pthread_mutex_t	*fork;
	int				fin_eat;
	pthread_mutex_t	fin_eat_mutex;
	long int		initial_time;
	int				is_fin;
	pthread_mutex_t	flag_mutex;
}	t_argset;

typedef struct s_philo
{
	int				id;
	long int		last_meal;
	pthread_mutex_t	last_meal_mutex;
	int				cnt_eat;
	pthread_mutex_t	cnt_eat_mutex;
	t_argset		*arg;
	pthread_t		thread;
	int				fork_right;
	int				fork_left;
}	t_philo;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long int	get_time(void);
void		ft_usleep(long int ms);

void		display(t_argset *arg, char *str, int id);
void		ft_wait(long int ms);
void		dobby_fork(t_argset *arg, int idx);
void		dobby_philo(t_philo *philo, int idx);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			init(int count, char **value);
int			init_mutex(t_argset *arg);
int			init_arg(t_argset *arg, int argc, char *argv[]);
int			init_philo(t_philo **philo, t_argset *arg);

int			check_update(t_argset *arg, int mode);
void		philo_fin(t_argset *arg, t_philo *philo);
void		philo_fin2(t_argset *arg, t_philo *philo);
void		*invoking(void *param);
int			threading(t_philo *philo, t_argset *arg);

void		philo_eat(t_argset *arg, t_philo *philo);
void		philo_sleep(t_argset *arg, t_philo *philo);
#endif
