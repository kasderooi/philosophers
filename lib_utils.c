/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lib_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kas <kas@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/05 13:33:37 by kas           #+#    #+#                 */
/*   Updated: 2021/09/21 10:46:16 by kde-rooi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static int	nbr_length(long nbr)
{
	unsigned int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (i < ft_strlen(str) && ft_isdigit(str[i]))
	{
		nbr *= 10;
		nbr += str[i] - 48;
		if (nbr > 9223372036854775807 || i > 19)
			return (-1);
		i++;
	}
	if (str[i] != 0)
		return (-1);
	return (nbr);
}

char	*ft_itoa(int n)
{
	int			len;
	long		nbr;
	char		*ret;

	nbr = (long)n;
	len = nbr_length(nbr);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	if (nbr < 0)
	{
		ret[0] = '-';
		nbr *= -1;
	}
	ret[len] = '\0';
	if (nbr == 0)
		ret[0] = '0';
	while (nbr)
	{
		len--;
		ret[len] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (ret);
}
