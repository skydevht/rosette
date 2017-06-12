//
// Created by Hash on 6/2/2016.
//

#ifndef ROSETTE_BUTTON_H
#define ROSETTE_BUTTON_H

#include <allegro5/allegro.h>
#include "circle_container.h"

enum Side {
    LEFT,
    RIGHT
};

typedef struct Button {
    float x, y;
    int width, height;
    ALLEGRO_BITMAP *main_bmp;
    ALLEGRO_BITMAP *default_bmp;
    ALLEGRO_BITMAP *hover_bmp;
    void (*click_handler)(void);
} Button;

Button *create_button(float x, float y, ALLEGRO_BITMAP *default_bmp, ALLEGRO_BITMAP *hover_bmp);

void draw_button(Button *button);
void destroy_button(Button *button);

void maj_button(Button *button);

#endif //ROSETTE_BUTTON_H
