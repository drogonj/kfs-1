#include "../../../include/kernel.h"

void	ft_putpointer(void *ptr)
{
	kputstr("0x");
	ft_puthex_lower((unsigned long int)(ptr), 0);
}
