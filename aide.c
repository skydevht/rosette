//
// Created by Hash on 7/11/2016.
//
#include "defines.h"
#include "aide.h"
#include "clavier.h"

int id(){
    return ROSETTE_ETAT_AIDE;
}

void init_aide(){

}

int maj_aide(){
    if (clavier_touche_relachee(ALLEGRO_KEY_ESCAPE)) return ROSETTE_ETAT_MENU_PRINCIPAL;
    return id();
}

void afficher_aide(){
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void deinit_aide(){

}


void creer_aide(ETATJEU *etatjeu){
    etatjeu->id = id;
    etatjeu->init = init_aide;
    etatjeu->maj = maj_aide;
    etatjeu->afficher = afficher_aide;
    etatjeu->deinit = deinit_aide;
}