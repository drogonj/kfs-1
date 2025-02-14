#ifndef COLORS_H
# define COLORS_H

# define BLACK         0x0
# define BLUE          0x1
# define GREEN         0x2
# define CYAN          0x3
# define RED           0x4
# define MAGENTA       0x5
# define BROWN         0x6
# define LIGHT_GREY    0x7
# define DARK_GREY     0x8
# define LIGHT_BLUE    0x9
# define LIGHT_GREEN   0xA
# define LIGHT_CYAN    0xB
# define LIGHT_RED     0xC
# define LIGHT_MAGENTA 0xD
# define YELLOW        0xE
# define WHITE         0xF

// Make a foreground/background color
# define VGA_COLOR(fg, bg) ((bg << 4) | (fg))

#endif