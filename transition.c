//
// Created by Hash on 4/14/2016.
//

#include "transition.h"
#include "global.h"

TRANSITION *creer_transition(ETATJEU *de, ETATJEU *vers, double duree) {
    TRANSITION *t = malloc(sizeof(TRANSITION));

    t->de = de;
    t->vers = vers;
    t->duree = duree;
    t->progres = 0.0f;

    t->de_bmp = al_create_bitmap(largeur_ecran, hauteur_ecran);
    al_set_target_bitmap(t->de_bmp);
    if (de) {
        de->afficher();
    } else {
        al_clear_to_color(al_map_rgb_f(0, 0, 0));
    }
    al_set_target_backbuffer(ecran);

    t->vers_bmp = al_create_bitmap(largeur_ecran, hauteur_ecran);
    al_set_target_bitmap(t->vers_bmp);

    if (vers) {
        vers->afficher();
    } else {
        al_clear_to_color(al_map_rgb_f(0, 0, 0));
    }
    al_set_target_backbuffer(ecran);
    return t;
}

void detruire_transition(TRANSITION *t) {
    if (t->vers_bmp) {
        al_destroy_bitmap(t->vers_bmp);
        t->vers_bmp = NULL;
    }
    if (t->de_bmp) {
        al_destroy_bitmap(t->de_bmp);
        t->de_bmp = NULL;
    }

    free(t);
    t = NULL;
}

int maj_transition(TRANSITION *t) {
    t->progres += 1.0f / logic_framerate;
    if (t->progres >= t->duree) {
        return 0;
    } else {
        return 1;
    }
}

int afficher_transition(TRANSITION *t) {
    int x = (int) (t->progres * largeur_ecran / t->duree);
    al_draw_bitmap_region(t->vers_bmp, 0, 0, x, hauteur_ecran, largeur_ecran -x, 0, 0);
    al_draw_bitmap_region(t->de_bmp, x, 0, largeur_ecran- x , hauteur_ecran, 0, 0, 0);
}