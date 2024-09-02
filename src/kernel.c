#include<kernel.h>
#include<vga.h>

const char* mystr = "hola, mundo";

void kernel(){

    struct VgaDevice vga = vga_new();
    vga_puts(&vga, "Hello, world");

    while(1){}

}
