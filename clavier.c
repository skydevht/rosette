//
// Created by Hash on 6/15/2016.
//

#include "clavier.h"

#define KEYBUFF_SIZE 16

static int tableau_touche[ALLEGRO_KEY_MAX];
static int tableau_unicode[KEYBUFF_SIZE];
static int nombre_unicode;

bool clavier_touche_pressee(int k) {
    return tableau_touche[k] & 1;
}

bool clavier_touche_relachee(int k) {
    return tableau_touche[k] & 2;
}

void clavier_gerer_evenement(ALLEGRO_EVENT *event) {
    switch (event->type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            tableau_touche[event->keyboard.keycode] |= (1 << 0);
            tableau_touche[event->keyboard.keycode] |= (1 << 1);
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            if (event->keyboard.unichar && nombre_unicode < KEYBUFF_SIZE){
                tableau_unicode[nombre_unicode++] = event->keyboard.unichar;
            }
            break;
        case ALLEGRO_KEY_UP:
            tableau_touche[event->keyboard.keycode] &= ~(1 << 0);
            tableau_touche[event->keyboard.keycode] |= (1 << 2);
            break;
    }
}

void clavier_tick(){
    int i;
    for (i = 0; i < ALLEGRO_KEY_MAX; i++){
        tableau_touche[i] &= ~(1 << 1);
        tableau_touche[i] &= ~(1 << 2);
    }
}
