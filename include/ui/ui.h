#ifndef UI_H
#define UI_H

#include<vga.h>

// A UI driver
struct Ui;

// A widget object
struct Widget{
    void* this;
    
};

// Creates a new Ui instance borrowing (mutably) the given vga
struct Ui* ui_make(struct VgaDevice* vga);

// Draws a widget
void ui_draw(struct Widget);

// Takes ownership of `ui` and frees the underlying resources
void ui_free(struct Ui* ui);

#endif
