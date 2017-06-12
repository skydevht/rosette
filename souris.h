//
// Created by Hash on 4/14/2016.
//

#ifndef ROSETTE_MOUSE_H
#define ROSETTE_MOUSE_H

#include <stdbool.h>

#include "global.h"

bool souris_bouton_presse(int b);
bool souris_bouton_relache(int b);
int souris_x(void);
int souris_y(void);

void souris_gerer_evenement(ALLEGRO_EVENT *event);
void souris_tick(void);


#endif //ROSETTE_MOUSE_H
