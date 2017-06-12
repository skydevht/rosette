//
// Created by Hash on 6/2/2016.
//

#include <allegro5/allegro_primitives.h>
#include "circle_container.h"

CircleContainer* create_circle_container(float x, float y, int radius){
    CircleContainer *circleContainer = malloc(sizeof(circleContainer));
    circleContainer->x = x;
    circleContainer->y = y;
    circleContainer->outer_radius = radius;
    return circleContainer;
}

void draw_circle_container(CircleContainer *circleContainer){
    al_draw_circle(circleContainer->x, circleContainer->y, circleContainer->outer_radius, al_map_rgb(22, 155, 131), 7);
    al_draw_circle(circleContainer->x, circleContainer->y, circleContainer->outer_radius - 25, al_map_rgb(22, 155, 131), 30);
    al_draw_circle(circleContainer->x, circleContainer->y, circleContainer->outer_radius - 50, al_map_rgba_f(0.09, 0.61, 0.51, 0.9), 6);
}
