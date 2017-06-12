//
// Created by Hash on 4/21/2016.
//

#ifndef ROSETTE_INTRO_H
#define ROSETTE_INTRO_H

#include <allegro5/allegro.h>
#include "global.h"
#include "etatjeu.h"

void creer_intro(ETATJEU *etat);
void draw_intro(void);
int intro_id(void);
void init_intro(void);
void afficher_intro(void);
int maj_intro(void);
void deInit_intro(void);

#endif //ROSETTE_INTRO_H
