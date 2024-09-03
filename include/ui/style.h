#ifndef UI_STYLE_H
#define UI_STYLE_H

#define BLACK        0
#define BLUE         1
#define GREEN        2
#define CYAN         3
#define RED          4
#define PINK         5
#define ORANGE       6
#define LIGHT_GRAY   7
#define GRAY         8
#define LIGHT_BLUE   9
#define LIGHT_GREEN  10
#define LIGHT_CYAN   11
#define LIGHT_RED    12
#define LIGHT_PINK   13
#define LIGHT_ORANGE 14
#define WHITE  15

#define STYLE(back,fore) (char)(( \
        ( (back&0b1111)<<4 )|\
        ( (fore&0b1111) )\
))

#endif
