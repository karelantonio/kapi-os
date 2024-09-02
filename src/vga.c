#include<vga.h>

struct VgaDevice vga_new() {
    struct VgaDevice dev = {
        (char*)0xb8000, 0
    };
    return dev;
}

void vga_putc(struct VgaDevice* devp, char c) {
    devp->address[devp->ptr] = c;
    devp->ptr+=2;
}

void vga_hex32(struct VgaDevice* devp, unsigned long n) {
    char dgs[10];
    dgs[0]='0';
    dgs[1]='x';
    for(int i = 0; i<8; i++){
        char c = n&0xf;
        n>>=4;
        if(c<10) c+= '0';
        else if(c<16) c+= 'a' - 10;
        dgs[9-i] = c;
    }
    for(int i = 0; i<10; i++){
        devp->address[devp->ptr] = dgs[i];
        devp->ptr+=2;
    }
}

void vga_puts(struct VgaDevice* devp, const char *str) {
    while(*str){
        devp->address[devp->ptr] = *str;
        devp->ptr+=2;
        str++;
    }
}

void vga_newline(struct VgaDevice* devp) {
    devp->address[devp->ptr] = '\n';
    devp->ptr+=2;
}
