#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <allegro5/allegro.h>
#include "etatjeu.h"
#include "global.h"
#include "hud.h"
#define J1 0
#define J2 1

extern void creer_nouveau_jeu(ETATJEU *etat);
extern void creer_continuer_jeu(ETATJEU *etat);
extern void detruire_jeu(void);

void changer_joueur(int ancien_joueur);

Player * trouver_joueur_actif();

void augmenter_score(int couleur_pion_pris, int score);

void terminer_jeu();

#endif // JEU_H_INCLUDED
