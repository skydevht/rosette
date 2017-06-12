//
// Created by Hash on 6/2/2016.
//

#ifndef ROSETTE_CIRCLE_CONTAINER_H
#define ROSETTE_CIRCLE_CONTAINER_H

#include <allegro5/allegro.h>

typedef struct CircleContainer {
    float x, y;
    int outer_radius;
} CircleContainer;

CircleContainer* create_circle_container(float x, float y, int radius);

void draw_circle_container(CircleContainer *circleContainer);

#endif //ROSETTE_CIRCLE_CONTAINER_H
