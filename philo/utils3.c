#include "./include/philosopher.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_update(t_argset *arg, int mode)
{
	int	res;

	pthread_mutex_lock(&arg->flag_mutex);
	if (mode == CHECK)
	{
		res = arg->is_fin;
		pthread_mutex_unlock(&arg->flag_mutex);
		return (res);
	}
	else
	{
		arg->is_fin = 1;
		pthread_mutex_unlock(&arg->flag_mutex);
	}
	return (0);
}
