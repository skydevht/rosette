//
// Created by Hash on 5/10/2016.
//

#ifndef ROSETTE_HUD_H
#define ROSETTE_HUD_H

#include "view.h"
#include "UI/button.h"


typedef struct Player {
    int id;
    int score;
    int pions_restants;
    int active;
    int color;
} Player;

typedef struct Hud{
    int x;
    int y;
    int width;
    int height;
    Player *player;
    char *title;
    Button *pass_btn;
    Button *quit_btn;
}Hud;

void init_hud(Hud *hud, int player);
void deinit_hud(Hud *hud);
void afficher_hud(Hud *hud);
void maj_hud(Hud *hud);

#endif //ROSETTE_HUD_H
