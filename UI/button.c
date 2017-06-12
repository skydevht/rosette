//
// Created by Hash on 6/2/2016.
//

#include <malloc.h>
#include <allegro5/allegro_font.h>
#include "button.h"
#include "../global.h"
#include "../defines.h"
#include "circle_container.h"
#include "../Util/hex.h"
#include "../souris.h"


Button *create_button(float x, float y, ALLEGRO_BITMAP *default_bmp, ALLEGRO_BITMAP *hover_bmp) {
    Button *button = malloc(sizeof(Button));
    button->default_bmp = default_bmp;
    button->main_bmp = default_bmp;
    button->hover_bmp = hover_bmp;
    button->x = x;
    button->y = y;
    button->width = al_get_bitmap_width(button->default_bmp);
    button->height = al_get_bitmap_height(button->default_bmp);
    return button;
}

void draw_button(Button *button) {
    float x, y;

    x = button->x - button->width / 2.0;
    y = button->y - button->height / 2.0;

    al_draw_bitmap(button->main_bmp, x, y, 0);
}
void destroy_button(Button *button) {
    free(button);
}

void maj_button(Button *button) {
    if (souris_x() > (button->x - button->width / 2.0) && souris_x() < (button->x + button->width / 2.0)) {
        if (souris_y() > (button->y - button->height / 2.0) && souris_y() < (button->y + button->height / 2.0)) {
            button->main_bmp = button->hover_bmp;
            if (souris_bouton_presse(1)) {
                button->click_handler();
            }
        } else {
            button->main_bmp = button->default_bmp;
        }
    } else {
        button->main_bmp = button->default_bmp;
    }
}