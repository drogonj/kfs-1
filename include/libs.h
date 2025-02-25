#ifndef LIBS_H
# define LIBS_H

// io
void outb(uint32_t port, uint8_t value);
uint8_t inb(uint32_t port);
void outw(uint32_t port, uint16_t value);
uint16_t inw(uint32_t port);
void outl(uint32_t port, uint32_t value);
uint32_t inl(uint32_t port);

// strings
char *ft_strchr(const char *s, int c);
int	ft_strcmp(const char *s1, const char *s2);
unsigned int ft_strlen(const char *s);

#endif