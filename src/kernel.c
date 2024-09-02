#include<kernel.h>
#include<vga.h>

void kernel(){

    struct VgaDevice vga = vga_new();
    vga_puts(&vga, "Hello, world");

    while(1){}

}
