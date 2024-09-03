#include<kernel.h>
#include<vga.h>

void kernel(){

    struct VgaDevice vga = vga_new();
    for(int r = 0; r<25; r++){
        for(int c = 0; c<80; c++){
            vga_putc(&vga, r, c, (c%10 + '0'), 0);
        }
    }

}
