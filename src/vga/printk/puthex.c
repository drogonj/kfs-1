#include "../../../include/kernel.h"

int	ft_puthex_lower(unsigned long int n, unsigned int len)
{
	const char	base[17] = "0123456789abcdef";
	int			lentmp;

	lentmp = 0;
	if (n >= 16)
	{
		lentmp = ft_puthex_lower(n / 16, len);
		len += lentmp;
		ft_puthex_lower(n % 16, len);
	}
	else
	{
		kputchar(base[n]);
	}
	return (++len);
}

int	ft_puthex_upper(unsigned long int n, unsigned int len)
{
	const char	base[17] = "0123456789ABCDEF";
	int			lentmp;

	lentmp = 0;
	if (n >= 16)
	{
		lentmp = ft_puthex_upper(n / 16, len);
		len += lentmp;
		ft_puthex_upper(n % 16, len);
	}
	else
	{
        kputchar(base[n]);
	}
	return (++len);
}