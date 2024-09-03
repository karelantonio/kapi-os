#include<vga.h>

struct VgaDevice vga_new() {
    struct VgaDevice dev = {
        (char*)0xb8000, 25, 80
    };
    return dev;
}

void vga_putc(struct VgaDevice* devp, int r, int c, char chr, char style) {
    if( c < 0 || devp->cols <= c )return;
    if( r < 0 || devp->rows <= r )return;
    devp->address[2*r*(devp->cols) + 2*c] = chr;
    devp->address[2*r*(devp->cols) + 2*c+1] = style;
}

