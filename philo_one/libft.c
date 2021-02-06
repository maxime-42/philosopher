#include "philo.h"

static int     ft_strlen(char *str)
{
    int index;

    index = 0;
    while (str[index])
    {
        index++;
    }
    return (index);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int     print_error(char *msg)
{
    int nb_bytes;

    nb_bytes = ft_strlen(msg);
    write(2, msg, nb_bytes);
    return (ERROR);
}

int     str_is_digit(char *str)
{
    int index;
    int ret;

    index = -1;
    while (str[++index])
    {
        ret = ft_isdigit(str[index]);
        if (ret == 0)
            return (ERROR);
    }
    return (SUCCESS);
}

int			ft_atoi(const char *nptr)
{
	long	n;
	int		s;
	int		ovf;

	n = 0;
	s = 1;
	ovf = 1;
	while ((*nptr && *nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if ((*nptr && *nptr == '-') || *nptr == '+')
	{
		if (*nptr == '-')
			s *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9' && ovf == 1)
	{
		n = (n * 10) + *nptr++ - 48;
		if (n < 0 && s == 1)
			ovf = -1;
		else if (n < 0 && s == -1)
			ovf = 0;
	}
	return (ovf == 1 ? n * s : ovf);
}