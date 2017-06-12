//
// Created by Hash on 4/14/2016.
//

#ifndef ROSETTE_TRANSITION_H
#define ROSETTE_TRANSITION_H

#include <allegro5/allegro.h>
#include "transition.h"
#include "etatjeu.h"

typedef struct {
    ETATJEU *de;
    ETATJEU *vers;
    double duree;
    double progres;
    ALLEGRO_BITMAP *de_bmp;
    ALLEGRO_BITMAP *vers_bmp;
} TRANSITION;

TRANSITION *creer_transition(ETATJEU *de, ETATJEU *vers, double duree);
void detruire_transition(TRANSITION *t);
int maj_transition(TRANSITION *t);
int afficher_transition(TRANSITION *t);

#endif //ROSETTE_TRANSITION_H
