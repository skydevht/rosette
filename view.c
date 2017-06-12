//
// Created by Hash on 5/10/2016.
//

#include <malloc.h>
#include <allegro5/haptic.h>
#include "view.h"
#include "global.h"

View * create_view(char *name, View *parent, int x, int y, int w, int h){
    View *view = malloc(sizeof(View));
    view->bmp = al_create_bitmap(w, h);
    view->parent = (parent == 0) ? NULL : parent;
    view->name = name;
    view->x = x;
    view->y = y;
    view->w = w;
    view->h = h;
}

void draw_view(View *view){
    ALLEGRO_BITMAP *last_bmp = al_get_target_bitmap();
    if (view->parent) al_set_target_bitmap(view->parent->bmp);
    al_draw_bitmap(view->bmp, view->x, view->y, 0);
    al_set_target_bitmap(last_bmp);
}

void destroy_view(View *view){
    al_destroy_bitmap(view->bmp);
    free(view);
}