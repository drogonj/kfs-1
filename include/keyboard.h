#ifndef KEYBOARD_H
# define KEYBOARD_H

# define KBD_MAP_SIZE 128

#define KBD_MAP_SIZE 128

static char KBD_MAP[KBD_MAP_SIZE] = {
    '\0',  // 0x00
    '\0',  // 0x01 Esc
    '1',   // 0x02
    '2',   // 0x03
    '3',   // 0x04
    '4',   // 0x05
    '5',   // 0x06
    '6',   // 0x07
    '7',   // 0x08
    '8',   // 0x09
    '9',   // 0x0A
    '0',   // 0x0B
    '-',   // 0x0C
    '=',   // 0x0D
    '\0',  // 0x0E Backspace
    '\t',  // 0x0F Tab
    'q',   // 0x10
    'w',   // 0x11
    'e',   // 0x12
    'r',   // 0x13
    't',   // 0x14
    'y',   // 0x15
    'u',   // 0x16
    'i',   // 0x17
    'o',   // 0x18
    'p',   // 0x19
    '[',   // 0x1A
    ']',   // 0x1B
    '\n',  // 0x1C Enter
    '\0',  // 0x1D Left Ctrl
    'a',   // 0x1E
    's',   // 0x1F
    'd',   // 0x20
    'f',   // 0x21
    'g',   // 0x22
    'h',   // 0x23
    'j',   // 0x24
    'k',   // 0x25
    'l',   // 0x26
    ';',   // 0x27
    '\'',  // 0x28
    '`',   // 0x29
    '\0',  // 0x2A Left Shift
    '\\',  // 0x2B
    'z',   // 0x2C
    'x',   // 0x2D
    'c',   // 0x2E
    'v',   // 0x2F
    'b',   // 0x30
    'n',   // 0x31
    'm',   // 0x32
    ',',   // 0x33
    '.',   // 0x34
    '/',   // 0x35
    '\0',  // 0x36 Right Shift
    '*',   // 0x37 Keypad *
    '\0',  // 0x38 Left Alt
    ' ',   // 0x39 Space
    '\0',  // 0x3A Caps Lock
    '\0',  // 0x3B F1
    '\0',  // 0x3C F2
    '\0',  // 0x3D F3
    '\0',  // 0x3E F4
    '\0',  // 0x3F F5
    '\0',  // 0x40 F6
    '\0',  // 0x41 F7
    '\0',  // 0x42 F8
    '\0',  // 0x43 F9
    '\0',  // 0x44 F10
    '\0',  // 0x45 Num Lock
    '\0',  // 0x46 Scroll Lock
    '\0',  // 0x47 Keypad 7
    '\0',  // 0x48 Keypad 8
    '\0',  // 0x49 Keypad 9
    '\0',  // 0x4A Keypad -
    '\0',  // 0x4B Keypad 4
    '\0',  // 0x4C Keypad 5
    '\0',  // 0x4D Keypad 6
    '\0',  // 0x4E Keypad +
    '\0',  // 0x4F Keypad 1
    '\0',  // 0x50 Keypad 2
    '\0',  // 0x51 Keypad 3
    '\0',  // 0x52 Keypad 0
    '\0',  // 0x53 Keypad .
    '\0',  // 0x54
    '\0',  // 0x55
    '\0',  // 0x56
    '\0',  // 0x57 F11
    '\0',  // 0x58 F12
    '\0',  // Remaining entries filled with '\0'
    [0x59 ... 0x7F] = '\0'
};

static char KBD_MAP_SHIFT[KBD_MAP_SIZE] = {
    '\0',  // 0x00
    '\0',  // 0x01 Esc
    '!',   // 0x02 (Shift + 1)
    '@',   // 0x03 (Shift + 2)
    '#',   // 0x04 (Shift + 3)
    '$',   // 0x05 (Shift + 4)
    '%',   // 0x06 (Shift + 5)
    '^',   // 0x07 (Shift + 6)
    '&',   // 0x08 (Shift + 7)
    '*',   // 0x09 (Shift + 8)
    '(',   // 0x0A (Shift + 9)
    ')',   // 0x0B (Shift + 0)
    '_',   // 0x0C (Shift + -)
    '+',   // 0x0D (Shift + =)
    '\0',  // 0x0E Backspace
    '\t',  // 0x0F Tab
    'Q',   // 0x10 (Shift + q)
    'W',   // 0x11 (Shift + w)
    'E',   // 0x12 (Shift + e)
    'R',   // 0x13 (Shift + r)
    'T',   // 0x14 (Shift + t)
    'Y',   // 0x15 (Shift + y)
    'U',   // 0x16 (Shift + u)
    'I',   // 0x17 (Shift + i)
    'O',   // 0x18 (Shift + o)
    'P',   // 0x19 (Shift + p)
    '{',   // 0x1A (Shift + [)
    '}',   // 0x1B (Shift + ])
    '\n',  // 0x1C Enter
    '\0',  // 0x1D Left Ctrl
    'A',   // 0x1E (Shift + a)
    'S',   // 0x1F (Shift + s)
    'D',   // 0x20 (Shift + d)
    'F',   // 0x21 (Shift + f)
    'G',   // 0x22 (Shift + g)
    'H',   // 0x23 (Shift + h)
    'J',   // 0x24 (Shift + j)
    'K',   // 0x25 (Shift + k)
    'L',   // 0x26 (Shift + l)
    ':',   // 0x27 (Shift + ;)
    '"',   // 0x28 (Shift + ')
    '~',   // 0x29 (Shift + `)
    '\0',  // 0x2A Left Shift
    '|',   // 0x2B (Shift + \)
    'Z',   // 0x2C (Shift + z)
    'X',   // 0x2D (Shift + x)
    'C',   // 0x2E (Shift + c)
    'V',   // 0x2F (Shift + v)
    'B',   // 0x30 (Shift + b)
    'N',   // 0x31 (Shift + n)
    'M',   // 0x32 (Shift + m)
    '<',   // 0x33 (Shift + ,)
    '>',   // 0x34 (Shift + .)
    '?',   // 0x35 (Shift + /)
    '\0',  // 0x36 Right Shift
    '*',   // 0x37 Keypad *
    '\0',  // 0x38 Left Alt
    ' ',   // 0x39 Space
    '\0',  // 0x3A Caps Lock
    '\0',  // 0x3B F1
    '\0',  // 0x3C F2
    '\0',  // 0x3D F3
    '\0',  // 0x3E F4
    '\0',  // 0x3F F5
    '\0',  // 0x40 F6
    '\0',  // 0x41 F7
    '\0',  // 0x42 F8
    '\0',  // 0x43 F9
    '\0',  // 0x44 F10
    '\0',  // 0x45 Num Lock
    '\0',  // 0x46 Scroll Lock
    '\0',  // 0x47 Keypad 7
    '\0',  // 0x48 Keypad 8
    '\0',  // 0x49 Keypad 9
    '\0',  // 0x4A Keypad -
    '\0',  // 0x4B Keypad 4
    '\0',  // 0x4C Keypad 5
    '\0',  // 0x4D Keypad 6
    '\0',  // 0x4E Keypad +
    '\0',  // 0x4F Keypad 1
    '\0',  // 0x50 Keypad 2
    '\0',  // 0x51 Keypad 3
    '\0',  // 0x52 Keypad 0
    '\0',  // 0x53 Keypad .
    '\0',  // 0x54
    '\0',  // 0x55
    '\0',  // 0x56
    '\0',  // 0x57 F11
    '\0',  // 0x58 F12
    '\0',  // Remaining entries filled with '\0'
    [0x59 ... 0x7F] = '\0'
};

#endif