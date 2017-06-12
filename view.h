//
// Created by Hash on 5/10/2016.
//

#ifndef ROSETTE_VIEW_H
#define ROSETTE_VIEW_H

#include <allegro5/bitmap.h>

typedef struct View {
    char *name;
    struct View *parent;
    ALLEGRO_BITMAP * bmp;
    int w;
    int h;
    int x;
    int y;
}View;

View * create_view(char *name, View *parent, int x, int y, int w, int h);
void draw_view(View *view);
void destroy_view(View *view);

#endif //ROSETTE_VIEW_H
