//
// Created by Hash on 5/10/2016.
//

#include <allegro5/haptic.h>
#include "hud.h"
#include "jeu.h"


ALLEGRO_COLOR primary;

Hud *current_hud;

void pass_click_handler(){
    Player *joueur_actif = trouver_joueur_actif();
    if (joueur_actif->id == current_hud->player->id) changer_joueur(joueur_actif->id);
}

void hud_quit_click_handler(){
    terminer_jeu();
}

void init_hud(Hud *hud, int player) {
    char *title = malloc(sizeof(char) * 5);
    primary = al_map_rgb(0, 150, 135);

    hud->x = (player == J1) ? 0 : 3*largeur_ecran/4.0;
    hud->y = 0;
    hud->width = largeur_ecran /4.0;
    hud->height = hauteur_ecran;
    sprintf(title, "J%d", player + 1);
    hud->title = title;
    hud->pass_btn = create_button(hud->x + hud->width/2.0, 0.75 * hauteur_ecran, donnee_rosette[ROSETTE_GAME_PASS_BTN].dat, donnee_rosette[ROSETTE_GAME_PASS_BTN_HOVER].dat);
    hud->pass_btn->click_handler = pass_click_handler;
    hud->quit_btn = create_button(hud->x + hud->width/2.0, 0.75 * hauteur_ecran +100, donnee_rosette[ROSETTE_GAME_QUIT_BTN].dat, donnee_rosette[ROSETTE_GAME_QUIT_BTN_HOVER].dat);
    hud->quit_btn->click_handler = hud_quit_click_handler;
}

void deinit_hud(Hud *hud) {
    free(hud->title);
    destroy_button(hud->pass_btn);
    destroy_button(hud->quit_btn);
}

void afficher_hud(Hud *hud) {
    int center_x = hud->x + hud->width/2.0;
    int center_y = hud->y + hud->height/2.0;
    
    
    al_draw_filled_rectangle(hud->x, hud->y, hud->x + hud->width, hud->y + hud->height, al_map_rgba_f(0, 0, 0, 0.3));
    // affiche tit la
    al_draw_text(donnee_rosette[ROSETTE_HUD_TITLE_FONT].dat, primary, center_x, hud->y + 20, ALLEGRO_ALIGN_CENTER, hud->title);
    al_draw_line(hud->x, hud->y + 100, hud->x + hud->width, hud->y + 100, primary, 1);

    //afiche sko a
    char score[6];
    snprintf(score, 6, "%d", hud->player->score);
    double title_x = center_x - al_get_text_width(donnee_rosette[ROSETTE_HUD_TITLE_FONT].dat, score) / 2.0;
    al_draw_text(donnee_rosette[ROSETTE_HUD_TITLE_FONT].dat, primary, center_x, hud->y + 150, ALLEGRO_ALIGN_CENTER, score);


    // afiche pyon ki rete pou jwe
    int pions_restants = hud->player->pions_restants;
    char left_pawns[20];
    snprintf(left_pawns, 20, "%d %s", pions_restants, (pions_restants>1) ? "pions restants" : "pion restant");
    double x = (hud->width - 32) * pions_restants/150.0;
    al_draw_line(hud->x + 16, hud->y + 300, hud->x + hud->width - 16, hud->y + 300, al_map_rgba_f(0, 0, 0, 0.7), 7);
    al_draw_line(hud->x + 16, hud->y + 300, hud->x + 16 + x, hud->y + 300, al_map_rgb(22, 155, 131), 7);
    al_draw_text(donnee_rosette[ROSETTE_HUD_LEFT_PAWN_FONT].dat, primary, hud->x + hud->width - 16, hud->y + 315, ALLEGRO_ALIGN_RIGHT, left_pawns);
    draw_button(hud->pass_btn);
    draw_button(hud->quit_btn);

}

void maj_hud(Hud *hud) {
    current_hud = hud;
    maj_button(hud->pass_btn);
    maj_button(hud->quit_btn);
}
