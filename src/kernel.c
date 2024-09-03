#include<kernel.h>
#include<vga.h>
#include<alloc.h>
#include<alloc_arena.h>

void kernel(){
    arena_allocator(0x100000, 0x100000);
    allocator_setup();

    struct VgaDevice vga = vga_new();
    for(int r = 0; r<25; r++){
        for(int c = 0; c<80; c++){
            vga_putc(&vga, r, c, (c%10 + '0'), 0);
        }
    }

    allocator_destroy();
}
