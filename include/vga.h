#ifndef VGA_H
#define VGA_H

// The VGA Driver
struct VgaDevice{
    char *address;
    int rows;
    int cols;
};

// Create a new VGA Device
struct VgaDevice vga_new();

// Put a character into the VGA Device
void vga_putc(struct VgaDevice*, int r, int c, char chr, char style);

#endif
