#include<kernel.h>
#include<vga.h>
#include<alloc.h>
#include<alloc_arena.h>
#include<ui/canvas.h>
#include<ui/style.h>

void kernel(){
    arena_allocator(0x100000, 0x100000);
    allocator_setup();

    struct VgaDevice vga = vga_new();

    struct CanvasObject *obj = canvas_new(&vga);

    canvas_style(obj, BLACK, LIGHT_GRAY);
    canvas_fill_box(obj, 0, 0, 100000, 100000, ' ');
    canvas_draw_box(obj, 0, 0, 80, 25, '+', '+', '+', '+', '-', '|', '-', '|');
    canvas_draw_string(obj, 5, 0, "[ Ola caracola ]", -1);
    canvas_draw_string(obj, 6, 6, "Si vez ezto ezke funziona", -1);
    canvas_destroy(obj);

    /*for(int i = 0; i<255; i++){
        vga_putc(&vga, 0, i, i, 0);
    }*/

    allocator_destroy();
}
