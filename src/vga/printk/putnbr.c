#include "../../../include/kernel.h"

int	ft_putnbr(int n, unsigned int len)
{
	unsigned int	un;
	int				lentmp;

	lentmp = 0;
	if (n < 0)
	{
        kputchar('-');
		un = -n;
		len++;
	}
	else
		un = n;
	while (un > 9)
	{
		lentmp = ft_putnbr(un / 10, len);
		len = lentmp;
		un %= 10;
	}
    kputchar(un + '0');
	return (++len);
}

int	ft_putunsignednbr(unsigned int n, unsigned int len)
{
	int	lentmp;

	lentmp = 0;
	while (n > 9)
	{
		lentmp = ft_putnbr(n / 10, len);
		len = lentmp;
		n %= 10;
	}
    kputchar(n + '0');
	return (++len);
}
