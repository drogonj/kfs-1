# KFS-1, a kernel from scratch

**kfs-1** is about creating a kernel in **C** and **ASM x86**.

![](kfs1.gif)

### Base

* Based on i386 (x86) architecture
* Using **GRUB** as Bootloader (including multiboot support)

## Features

* **VGA support**
  * Print characters on screen
  * 8 bits color support
  * Auto-scroll support
  * Cursor support
    * Auto-newlines, or backwards
* **Interrupts**
  * Keyboard support
    * QWERTY keyboard support
    * RETURN supported (newlines)
    * DELETE supported
    * L_SHIFT -> 1234... -> !@#$...
    * L_CTRL+L -> clean the prompt
    * UP, LEFT, DOWN, RIGHT supported, moving the cursor
    * Change color with NUMPAD_0 or L_SHIFT+NUMPAD_0 (for background)
    * ESC -> switch to "Freemode" / "Promptmode"
  * **Interrupts Descriptor Table** setup
  * **Programmable Interrupt Controller** setup
* **Global Descriptor Table** setup
* **"Freemode"**
  * -> Disable prompt, clean the screen, and "unlock" directions keys (UP, RIGHT,..) making the cursor able to go in any directions
  * -> Nice feature for drawing 🖌 😄
* **Helpers** -> **printk()**
  * printf() but for kernel, pratical !
