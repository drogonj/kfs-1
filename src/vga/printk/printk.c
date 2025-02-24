#include "../../../include/kernel.h"

static int	ft_isformat(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'x' || c == 'X'
		|| c == '%')
		return (1);
	return (0);
}

static unsigned int    ft_argcount(const char *input)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (input[i])
	{
		if (input[i] == '%' && ft_isformat(input[i + 1]))
			res++;
		i++;
	}
	return (res);
}


static void	ft_outputformat(va_list args, char format)
{
	if (format == '%')
		kputchar('%');
	else if (format == 'c')
		kputchar(va_arg(args, int));
	else if (format == 's')
		kputstr(va_arg(args, char *));
	else if (format == 'p')
		ft_putpointer(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), 0);
	else if (format == 'u')
		ft_putunsignednbr(va_arg(args, unsigned int), 0);
	else if (format == 'x')
		ft_puthex_lower(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		ft_puthex_upper(va_arg(args, unsigned int), 0);
}

static void	ft_output(const char *input, va_list args, unsigned int argsnbr)
{
	unsigned int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1] && ft_isformat(input[i + 1])
			&& argsnbr-- > 0)
		{
			ft_outputformat(args, input[i++ + 1]);
		}
		else if (input[i] != '%')
		{
			kputchar(input[i]);
		}
		i++;
	}
}

void	printk(const char *input, ...)
{
	va_list         args;
	unsigned int	argsnbr;

	argsnbr = ft_argcount(input);
	va_start(args, input);
	ft_output(input, args, argsnbr);
	va_end(args);
}