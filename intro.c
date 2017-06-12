//
// Created by Hash on 4/21/2016.
//

#include "intro.h"
#include "clavier.h"

static double duration;
static double progress;

int intro_id(void) {
    return ROSETTE_ETAT_INTRO;
}

void init_intro(void) {
    duration = 4.0f;
    progress = 0.0f;
}


void afficher_intro(void) {
    float center_x = largeur_ecran /2.0;
    int y = 0.75 * hauteur_ecran;
    float x = (progress * 300) / duration;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(donnee_rosette[ROSETTE_INTRO_BG].dat, 0, 0, 1200, 675, 0, 0, largeur_ecran, hauteur_ecran, 0);
    al_draw_line(center_x - 300, y, center_x + 300, y, al_map_rgba_f(0, 0, 0, 0.7), 3);
    al_draw_line(center_x - x, y, center_x + x, y, al_map_rgb(22, 155, 131), 3);
}

void deInit_intro(void) {

}

int maj_intro(void) {
    progress += 1.0 / logic_framerate;

    if (progress >= duration) return ROSETTE_ETAT_MENU_PRINCIPAL;
    // skip intro
    if (clavier_touche_relachee(ALLEGRO_KEY_ESCAPE)) return ROSETTE_ETAT_MENU_PRINCIPAL;
    if (clavier_touche_relachee(ALLEGRO_KEY_SPACE)) return ROSETTE_ETAT_MENU_PRINCIPAL;
    if (clavier_touche_relachee(ALLEGRO_KEY_ENTER)) return ROSETTE_ETAT_MENU_PRINCIPAL;
    return intro_id();
}

void creer_intro(ETATJEU *etat) {
    etat->id = intro_id;
    etat->init = init_intro;
    etat->afficher = afficher_intro;
    etat->deinit = deInit_intro;
    etat->maj = maj_intro;
};