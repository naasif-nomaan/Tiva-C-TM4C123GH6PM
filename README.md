# Tiva-C-TM4C123GH6PM
My working practice with TM4C123GH6PM Microcontroller

Note:
(*((volatile unsigned long *) 0x400253FC))

It casts 0x400253FC as a volatile unsigned int pointer, and then dereferences that pointer to get the value of what 0x400253FC "points" to.

Note that 0x400253FC doesn't actually need to be declared as a pointer, it could as well be a literal integer that is then treated as an address to somewhere in memory. Useful on embedded systems or in kernel boot-up code where there are things at fixed addresses.
