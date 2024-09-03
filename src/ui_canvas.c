#include<ui/canvas.h>
#include<alloc.h>
#include<ptr_utils.h>
#include<math.h>

#define SWAP(a,b) do{\
    (a) += (b); \
    (b) = (a) - (b); \
    (a) -= (b); \
}while(0)

#define ENSURE_ORDER(a,b) do{\
    if( (a)>(b) ) { \
        SWAP( (a), (b) ); \
        (a) += 1; \
        (b) -= 1; \
    } \
}while(0)

#define XVALID(xpos) ( 0 <= (xpos) && (xpos) < (this->endx - this->offsetx) )
#define YVALID(ypos) ( 0 <= (ypos) && (ypos) < (this->endy - this->offsety) )

struct CanvasObject {
    struct VgaDevice* dev;
    int offsetx, offsety, endx, endy;
    char style;
};

// Create a new canvas, return NULL when an allocation failed
struct CanvasObject* canvas_new(struct VgaDevice* dev) {
    PROPAGATE_NULL(dev);
    struct CanvasObject* ptr = alloc(sizeof(struct CanvasObject));
    PROPAGATE_NULL(ptr);
    ptr->dev = dev;
    ptr->offsetx = 0;
    ptr->offsety = 0;
    ptr->endx = dev->cols;
    ptr->endy = dev->rows;
    ptr->style = 0;
    return ptr;
}

// Destroy a canvas (takes ownership)
void canvas_destroy(struct CanvasObject*this) {
    ABORT_ON_NULL(this);
    free(this);
}

// Borrow the vga device driver
struct VgaDevice* canvas_borrow_vga(struct CanvasObject*this){
    PROPAGATE_NULL(this);
    return this->dev;
}

// Create a new canvas, based on this, the calling function takes ownership
// Return NULL when an allocation failed
struct CanvasObject* canvas_subcanvas(struct CanvasObject*this, int offx, int offy, int endx, int endy) {
    PROPAGATE_NULL(this);
    struct CanvasObject* ptr = alloc(sizeof(struct CanvasObject));
    PROPAGATE_NULL(ptr);
    ptr->dev = this->dev;
    ptr->offsetx = this->offsetx + offx;
    ptr->offsety = this->offsety + offy;

    if(endx<=0)
        ptr->endx = this->endx + endx;
    else
        ptr->endx = endx;

    if(endy<=0)
        ptr->endy = this->endy + endy;
    else
        ptr->endy = endy;

    ptr->style = this->style;

    return ptr;
}

// Set the pen style (see the VGA styles)
void canvas_style(struct CanvasObject*this, char fore, char back) {
    ABORT_ON_NULL(this);
    this->style = ( fore&0b1111 ) | ((back& 0b1111)<<4);
}

// Draw an horizontal line, not included the end
void canvas_draw_hline(struct CanvasObject*this, int startx, int starty, int endx, char c) {
    ABORT_ON_NULL(this);
    ENSURE_ORDER(startx, endx);

    if (!XVALID(startx) ||
        !YVALID(starty))
        return;

    for(int x = startx; x<endx && x<this->endx - this->offsetx; x++){
        vga_putc(
                this->dev,
                this->offsety + starty,
                this->offsetx + x,
                c, this->style
        );
    }
}

// Draw a vertical line
void canvas_draw_vline(struct CanvasObject*this, int startx, int starty, int endy, char c) {
    ABORT_ON_NULL(this);
    if( starty>endy ) SWAP(starty, endy);

    if (!XVALID(startx) ||
        !YVALID(starty))
        return;

    for(int y = starty; y<endy && y< this->endy - this->offsety; y++){
        vga_putc(
                this->dev,
                this->offsety + y,
                this->offsetx + startx,
                c, this->style
        );
    }
}

// Draw a character
void canvas_draw_char(struct CanvasObject*this, int x, int y, char c) {
    ABORT_ON_NULL(this);
    if( !XVALID(x) ||
        !YVALID(y) ){
        return;
    }
    vga_putc(
            this->dev,
            this->offsety + y,
            this->offsetx + x,
            c, this->style
    );
}

// Draw a string
void canvas_draw_string(struct CanvasObject*this, int x, int y, const char* string, int maxsize) {
    ABORT_ON_NULL(this);
    ABORT_ON_NULL(string);
    int width = this->endx - this->offsetx;
    if( maxsize==-1 ){
        maxsize = width-x;
    }
    
    for(int i = 0; *string && i<maxsize && i+x<width; i++){
        vga_putc(
                this->dev,
                this->offsety + y,
                this->offsetx + x + i,
                *string, this->style
        );
        string++;
    }
}

// Draw a box
void canvas_draw_box(struct CanvasObject*this, int startx, int starty, int endx, int endy, char cornerTL, char cornerTR, char cornerBR, char cornerBL, char borderTop, char borderRight, char borderBottom, char borderLeft) {
    ABORT_ON_NULL(this);
    ENSURE_ORDER(startx, endx);
    ENSURE_ORDER(starty, endy);

    canvas_draw_char(this, startx, starty, cornerTL);
    canvas_draw_char(this, endx-1, starty, cornerTR);
    canvas_draw_char(this, endx-1, endy-1, cornerBR);
    canvas_draw_char(this, startx, endy-1, cornerBL);

    canvas_draw_vline(this, startx, starty+1, endy-1, borderLeft);
    canvas_draw_vline(this, endx-1, starty+1, endy-1, borderRight);
    canvas_draw_hline(this, startx+1, starty, endx-1, borderTop);
    canvas_draw_hline(this, startx+1, endy-1, endx-1, borderBottom);
}

// Fill a box
void canvas_fill_box(struct CanvasObject*this, int startx, int starty, int endx, int endy, char c) {
    ABORT_ON_NULL(this);
    ENSURE_ORDER(startx, endx);
    ENSURE_ORDER(starty, endy);

    if( !XVALID(startx) || !YVALID(starty) ){
        return;
    }

    for(int x = startx; x<endx && (x + this->offsetx < this->endx); x++){
        for(int y = starty; y<endy && (y + this->offsety < this->endy); y++){
            vga_putc(this->dev, y, x, c, this->style);
        }
    }
}
