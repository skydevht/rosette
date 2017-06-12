//
// Created by Hash on 4/14/2016.
//

#ifndef ROSETTE_BOARD_H
#define ROSETTE_BOARD_H
#include <allegro5/allegro_primitives.h>
#include "global.h"
#include "Util/hex.h"
#include "view.h"
#include "hud.h"

#define BOARD_OFFSET 7

#define  HEX_COUNT 140



typedef enum {
    P_WHITE,
    P_BLACK
} PionType;

typedef struct{
    int degre_liberte;
    int type;
} Pion;

typedef struct {
    Hex hex_position;
    Point pixel_position;
    int used;
    int white_count;
    int black_count;
} Hexagonal;

typedef struct Intersection {
    Vertex hex_position; //coordonnee dans le systeme hexagonal
    Point pixel_position; // position sur l'ecran
    Pion *pion;
    struct  Intersection *parent; //Lui-meme s'il est place avant tout autre
    int used;
    int hovered;
    int visited;
    int libre;
    struct Intersection *voisin[3];
} Intersection;

typedef struct {
    Hexagonal hexagonals[13][13];
    Intersection intersections[15][15][2];
} Board;

extern Board board;

int pion_suivant();


void creer_hexagone(int q, int r, int s);

void init_board();
void deinit_board();
void afficher_board();
void afficher_hexagone(Hex *hex);
int maj_board();

Hexagonal *trouver_hexagone(int q, int r, int s);
Intersection *trouver_intersection(Vertex vert);
void trouver_intersections_voisins(Intersection *inter);

void check_group(Intersection *inter, Intersection *last_inter_play);

int init_intersections(const Vertex *verts);

int check_from(Intersection *inter);

#endif //ROSETTE_BOARD_H
