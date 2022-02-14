#include "libft.h"

static int	ft_nbrlen(int nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
	{
		len++;
		nbr = nbr * (-1);
	}
	while (nbr >= 10)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_nbrlen(n);
	str = ((char *)malloc(sizeof(char) * (i + 1)));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n = (n / 10);
		i--;
	}
	return (str);
}
