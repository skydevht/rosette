//
// Created by Hash on 6/2/2016.
//


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "defines.h"
#include "menus.h"
#include "etatjeu.h"
#include "global.h"
#include "UI/circle_container.h"
#include "UI/button.h"

ALLEGRO_BITMAP *title;
Button *play_btn;
Button *help_btn;
Button *quit_btn;
int next_state;
int new = 1;

void play_click_handler(){
    next_state = ROSETTE_ETAT_NOUVEAU_JEU;
}

void resume_game_click_handler(){
    next_state = ROSETTE_ETAT_CONTINUER_JEU;
}

void help_click_handler(){
    next_state = ROSETTE_ETAT_AIDE;
}

void quit_click_handler(){
    next_state = ROSETTE_ETAT_SORTIE;
}

int menu_principal_id(void) {
    return ROSETTE_ETAT_MENU_PRINCIPAL;
}

void init_menu_principal(void) {
    next_state = ROSETTE_ETAT_MENU_PRINCIPAL;
    title = donnee_rosette[ROSETTE_MAIN_MENU_TITLE].dat;
    // Kreye bouton yo nan meni an
    if (new) {
        play_btn = create_button(0.80 * largeur_ecran, 0.32 * hauteur_ecran, donnee_rosette[ROSETTE_MAIN_MENU_PLAY_BTN].dat, donnee_rosette[ROSETTE_MAIN_MENU_PLAY_BTN_HOVER].dat);
        play_btn->click_handler = play_click_handler;
    } else {
        play_btn = create_button(0.78 * largeur_ecran, 0.18 * hauteur_ecran, donnee_rosette[ROSETTE_MAIN_MENU_RESUME_BTN].dat, donnee_rosette[ROSETTE_MAIN_MENU_RESUME_BTN_HOVER].dat);
        play_btn->click_handler = resume_game_click_handler;
    }
    help_btn = create_button(0.2 * largeur_ecran, 0.17 * hauteur_ecran, donnee_rosette[ROSETTE_MAIN_MENU_HELP_BTN].dat, donnee_rosette[ROSETTE_MAIN_MENU_HELP_BTN_HOVER].dat);
    help_btn->click_handler = help_click_handler;
    quit_btn = create_button(0.73 * largeur_ecran, 0.87 * hauteur_ecran, donnee_rosette[ROSETTE_MAIN_MENU_QUIT_BTN].dat, donnee_rosette[ROSETTE_MAIN_MENU_QUIT_BTN_HOVER].dat);
    quit_btn->click_handler = quit_click_handler;
}


void afficher_menu_principal(void) {
    float x, y;
    // tit meni an
    x = largeur_ecran/2.0 - al_get_bitmap_width(title)/2.0;
    y = hauteur_ecran/2.0 - al_get_bitmap_height(title)/2.0;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(donnee_rosette[ROSETTE_MAIN_BG].dat, 0, 0, 1200, 675, 0, 0, largeur_ecran, hauteur_ecran, 0);
    al_draw_bitmap(title, x, y, 0);
    //affiche bouton yo
    draw_button(play_btn);
    draw_button(help_btn);
    draw_button(quit_btn);

}

void deInit_menu_principal(void) {
    destroy_button(play_btn);
    destroy_button(help_btn);
    destroy_button(quit_btn);
}

int maj_menu_principal(void) {
    // jere bouton yo
    maj_button(play_btn);
    maj_button(help_btn);
    maj_button(quit_btn);
    return next_state;
}

void creer_menu_principal(ETATJEU *etat){
    etat->id = menu_principal_id;
    etat->init = init_menu_principal;
    etat->afficher = afficher_menu_principal;
    etat->maj = maj_menu_principal;
    etat->deinit = deInit_menu_principal;
}

void activer_continuer_jeu(){
    new = 0;
}

void activer_nouveau_jeu(){
    new = 1;
}

