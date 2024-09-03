#ifndef UI_CANVAS_H
#define UI_CANVAS_H
#include<vga.h>

// A canvas object (used internally)
struct CanvasObject;

// Create a new canvas, the calling canvas takes ownership
struct CanvasObject* canvas_new(struct VgaDevice* dev);

// Create a new canvas, based on this, the calling function takes ownership
struct CanvasObject* canvas_subcanvas(struct CanvasObject*this, int offx, int offy, int endx, int endy);

// Borrow the Vga
struct VgaDevice* canvas_borrow_vga(struct CanvasObject*this);

// Destroy a canvas (takes ownership)
void canvas_destroy(struct CanvasObject*this);

// Set the pen style
void canvas_style(struct CanvasObject*this, char fore, char bg);

// Draw an horizontal line, not included the end
void canvas_draw_hline(struct CanvasObject*this, int startx, int starty, int endx, char c);

// Draw a vertical line, not included the end
void canvas_draw_vline(struct CanvasObject*this, int startx, int starty, int endy, char c);

// Draw a character
void canvas_draw_char(struct CanvasObject*this, int x, int y, char c);

// Draw a string set maxsize to -1 to draw until end of canvas
void canvas_draw_string(struct CanvasObject*this, int x, int y, const char* string, int maxsize);

// Draw a box
void canvas_draw_box(struct CanvasObject*this, int startx, int starty, int endx, int endy, char cornerTL, char cornerTR, char cornerBR, char cornerBL, char borderTop, char borderRight, char borderBottom, char borderLeft);

// Fill a box
void canvas_fill_box(struct CanvasObject*this, int startx, int starty, int endx, int endy, char c);

#endif
