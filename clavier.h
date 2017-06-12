//
// Created by Hash on 6/15/2016.
//

#ifndef ROSETTE_CLAVIER_H
#define ROSETTE_CLAVIER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>

bool clavier_touche_pressee(int k);
bool clavier_touche_relachee(int k);
void clavier_gerer_evenement(ALLEGRO_EVENT *event);
void clavier_tick();



#endif //ROSETTE_CLAVIER_H
