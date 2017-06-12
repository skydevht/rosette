//
// Created by Hash on 4/14/2016.
//

#include <math.h>
#include "global.h"
#include "board.h"
#include "souris.h"
#include "logic.h"
#include "Util/hex.h"
#include "hud.h"
#include "jeu.h"

#define PRECISION 10
#define MIN(x, y) ((x > y) ? y : x)
#define TEST -3

Board board;
static PionType pionType = P_BLACK;
int largeur_board;
int hauteur_board;
int origin_x;
int origin_y;

double getHexagonSize();

void init_board() {
    // inisyalize varyab yo
    largeur_board = largeur_ecran / 2.0;
    hauteur_board = hauteur_ecran;
    origin_x = largeur_ecran/ 4.0;
    origin_y = 0;

    int i, j, k;
    for (i = -6; i <= 6; i++) {
        for (j = -6; j <= 6; j++) {
            for (k = -6; k <= 6; k++) {
                if (i + j + k == 0) { // kontrent po kowodone yo
                    // inisyalize egzagon nan si kowodonel respekte kontrent la
                    creer_hexagone(i, j, k);
                }
            }
        }
    }
}

void deinit_board() {
    int i, j, k;
    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++) {
            board.hexagonals[i][j].used = 0;
        }
    }
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            for (k = 0; k < 2; k++) {
                board.intersections[i][j][k].used = 0;
            }
        }
    }
}

void creer_hexagone(int q, int r, int s) {
    // chache adres pou stoke egzagon nan
    Hexagonal *hex = trouver_hexagone(q, r, s);

    // sil poko inisyalize
    if (hex->used != 1) {
        //stoke kowodone (egzagonal)
        hex->hex_position.q = q;
        hex->hex_position.r = r;
        hex->hex_position.s = s;
        // stoke pozisyon (pixel)
        hex_to_pixel(&hex->hex_position, &hex->pixel_position, getHexagonSize());
        // chache e stoke pozisyon (egzagonal) some egzagonal la
        Vertex verts[6];
        hex_corners(&hex->hex_position, verts);
        // inisyalize yo
        init_intersections(verts);
        hex->used = 1;
        hex->white_count = 0;
        hex->black_count = 0;
    }

}

int init_intersections(const Vertex *verts) {
    Intersection *intersection;
    for (int i = 0; i < 6; i++) {
        // stoke yon enteseksyon
        intersection = trouver_intersection(verts[i]);
        // si li pa inisyalize
        if (intersection->used != 1) {
            // stoke pozisyon (egzagonal)
            intersection->hex_position.q = verts[i].q;
            intersection->hex_position.r = verts[i].r;
            intersection->hex_position.side = verts[i].side;
            // ya, li poko gen pyon :)
            intersection->pion = NULL;
            //stoke pozisyon (pixel) li
            vertex_to_pixel(&intersection->hex_position, &intersection->pixel_position, getHexagonSize());
            // stoke adres sa ki vwazen li (enpotan!!!)
            trouver_intersections_voisins(intersection);
            // yep, nou fini ak inisyalizasyon an
            intersection->used = 1;
            intersection->visited = 0;
            intersection->hovered = 0;
            // e li toujou vid :)
            intersection->libre = 1;
        }
    }
}


Intersection *trouver_intersection(Vertex vert) {
    return &(board.intersections[vert.q + BOARD_OFFSET][vert.r + BOARD_OFFSET][vert.side]);;
}

void trouver_intersections_voisins(Intersection *inter) {
    // chache e stoke pozisyon (egzagonal) enteseksyon vwasen yo
    Vertex verts[3];
    adjacent_vertices(&inter->hex_position, verts);

    for (int i = 0; i < 3; i++) {
        // chache e stoke adres vwazen an
        inter->voisin[i] = trouver_intersection(verts[i]);
    }
}

double getHexagonSize() { return ((MIN(largeur_ecran, hauteur_ecran) - 60.0) / 26.0) / (sqrt(3.0) / 2.0); };

Hexagonal *trouver_hexagone(int q, int r, int s) {
    return &board.hexagonals[q + 6][r + 6];
};


void afficher_board() {
    int i, j, k;
    // sou tout eleman nan tablo <hexagonal> ki stoke nan <board>
    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++) {
            //stoke yon eleman
            Hexagonal *hex = &board.hexagonals[i][j];
            // si li fe pati de tablo a
            if (hex->used == 1) {
                // trase l
                afficher_hexagone(&(hex->hex_position));
            }
        }
    }
    // sou tout eleman nan tablo <intersections> ki stoke nan <board>
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            for (k = 0; k < 2; k++) {
                // stoke yon eleman
                Intersection *inter = &board.intersections[i][j][k];
                // si li fe pati de tablo a
                if (inter->used) {
                    // si li gen pyon
                    float px = inter->pixel_position.x + largeur_board / 2.0 + origin_x;
                    float py = -inter->pixel_position.y + hauteur_board / 2.0 + origin_y;
                    if (inter->pion) {


                        // li pozisyon (pixel) enteseksyon e konveti l nan repe ekran an
                        // swivan tip pyon an
                        switch (inter->pion->type) {
                            case P_WHITE:
                                // yon sek blan
                                al_draw_filled_circle(px, py, 10, al_map_rgb_f(1, 0, 0));
                                break;
                            case P_BLACK:
                                // yon sek nwa
                                al_draw_filled_circle(px, py, 10, al_map_rgb_f(0, 0, 1));
                                break;
                        }
                        if (inter->visited) {
                            al_draw_circle(px, py, 5, al_map_rgb_f(1, 0, 0), 1);
                        }
                    }
                    else if (inter->libre) {
                        al_draw_filled_circle(px, py, 3, al_map_rgb_f(1, 1, 1));
//                    } else if (inter->hex_position.r == TEST) {
//                        al_draw_filled_circle(px, py, 3, al_map_rgb_f(1, 0, 1));
                   }
                    if (inter->hovered) {
                        al_draw_filled_circle(px, py, 10, al_map_rgba_f(0, 0, 0, 0.5));
                   }
                }
            }
        }
    }
}

void afficher_hexagone(Hex *hex) {
    // kalkile pozisyon (pixel) orijin nan
    int cx = largeur_board / 2 + origin_x;
    int cy = hauteur_board / 2 + origin_y;

    //chache enteseksyon egzagon nan e stoke pozisyon (pixel) nan verts
    Vertex corners[6]; // pozisyon (egzagonal) enteseksyon yo
    hex_corners(hex, corners);
    Point verts[6];
    for (int i = 0; i < 6; i++) {
        Intersection *inter = trouver_intersection(corners[i]);
        verts[i].x = cx + inter->pixel_position.x;
        verts[i].y = cy - inter->pixel_position.y;
    }

    al_draw_polygon((float *) verts, 6, ALLEGRO_LINE_JOIN_MITER, al_map_rgb(0, 150, 136), 3, 1.0);
}




int maj_board() {
    Player *joueur_actif = trouver_joueur_actif();
    // si yo te klike souri a
    if (souris_bouton_relache(1)) {
        // stoke pozisyon (pixel) souri a e konvetil nan repe lokal damye a
        Point pt = {souris_x(), -souris_y()};
        pt.x -= (largeur_ecran / 2.0);
        pt.y += (hauteur_ecran / 2.0);
        // chache ki pozisyon (egzagonal) egzagon ki klike a
        Hex hex;
        pixel_to_hex(&pt, &hex, getHexagonSize());
        // jwenn pozisyon (egzagonal) some egzagonal la
        Vertex verts[6];
        hex_corners(&hex, verts);
        // kek varyab
        Point vPoint; // pozisyon (pixel) yon some
        int i; // konte
        for (i = 0; i < 6; i++) {
            // konveti pozisyon egzagonal yon some an pozisyon pixel
            vertex_to_pixel(&verts[i], &vPoint, getHexagonSize());
            // kalkile distans ant pozisyon souri a ak pozisyon some a
            int dist = distance_point(&pt, &vPoint);
            // si distans la pre some a
            if (dist < PRECISION) {
//                printf("la distance est de %d\n", dist);
//                printf("Les coords du point clique sont : (q = %d, r = %d, side = %d) de position (%f, %f)\n",
//                       verts[i].q, verts[i].r, verts[i].side, vPoint.x, vPoint.y);

                // chache adres enteseksyon ki se some a
                Intersection *inter = trouver_intersection(verts[i]);

                // verifye ke li lib
                if (inter->libre == 1) {
                    //verifye ke yo pap tou manje li
                    int counter = 0;
                    for (int j = 0; j < 3; j++){
                        if (!inter->voisin[j]->libre && inter->voisin[j]->used) {
                            if (inter->voisin[j]->pion->type != pionType) counter++;
                        }
                    };
                    if (counter == 3) return pionType;
                    // kreye yon antite pyon
                    Pion *pion = malloc(sizeof(Pion));
                    pion->type = (joueur_actif->id == J1) ? P_BLACK : P_WHITE;
                    joueur_actif->pions_restants--;//
                    // chanje tip pyon nou pral jwe apre sa
                    changer_joueur(joueur_actif->id);
                    // stoke adres antite a nan enteseksyon an
                    inter->pion = pion;
                    inter->libre = 0; // kounya, li pa lib :)

                    // fe mizajou egzagon li touche
                    Hex hexes[3];
                    vertex_touches(&inter->hex_position, hexes);
                    for (int j = 0; j < 3; j++) {
                        Hexagonal *hexagonal = trouver_hexagone(hexes[j].q, hexes[j].r, hexes[j].s);
                        switch (inter->pion->type) {
                            case P_WHITE:
                                hexagonal->white_count++;
                                break;
                            case P_BLACK:
                                hexagonal->black_count++;
                                break;
                        }
                    }

//                    for (int j = 0; j < 3; j++ ) {
//                        inter->voisin[j]->pion = pion;
//                        inter->voisin[j]->libre = 0;
//                    }

                    /* pati ki pi enpotan nan je a komanse la :)
                     *
                     * Nou pral kreye o maximum 4 gwoup, youn pou pyon
                     * nou sot plase a, youn pou chak pyon ki vwazen li si yo poko nan gwoup
                     * apre nap verifye ke yo pran gwoup la, e si se le ka, le nap detwi
                     * gwoup la nap tou detwi pyon yo
                     *
                     * */
                    check_from(inter);
                }
            }
        }
    }
    if (joueur_actif->pions_restants == 0) terminer_jeu();
    return pionType;
}

int check_from(Intersection *inter) {
    int score = 0;
    Groupe *groupes[4];
    printf("Groupe 1 :\n");
    groupes[0] = creer_groupe(inter);
    // kreye res yo
    for (int i = 1; i < 4; i++) {
        printf("Groupe %d :\n", i + 1);
        // si vwazen an pa deja nan yon gwoup
        if (!inter->voisin[i - 1]->visited) {
            // kreye youn ak li
            groupes[i] = creer_groupe(inter->voisin[i - 1]);
        }
        else {
            printf("Non cree\n");
            groupes[i] = NULL; // pou anpeche vale etranj
        }
    }
    // detwi yo tou swit apre
    for (int j = 0; j < 4; j++) {
        // verifye ke group la te kreye
        if (groupes[j]) {
            detruire_groupe(groupes[j], groupes[j]->pris);
        }
    }
    return 1;
}


int pion_suivant(){
    return pionType;
}