#ifndef VGA_H
#define VGA_H

// The VGA Driver
struct VgaDevice{
    char *address;
    long ptr;
};

// Create a new VGA Device
struct VgaDevice vga_new();

// Put a character into the VGA Device
void vga_putc(struct VgaDevice*, char);

// Put a whole string into the VGA Device
void vga_puts(struct VgaDevice*, const char *str);

// Put a new line into the VGA Device
void vga_newline(struct VgaDevice*);

// Write an hex number
void vga_hex32(struct VgaDevice*, unsigned long);


#endif
