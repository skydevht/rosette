//
// Created by Hash on 4/15/2016.
//

#ifndef ROSETTE_LOGIC_H
#define ROSETTE_LOGIC_H


#include "board.h"
#include "Util/data_struct.h"

typedef struct Groupe {
    int pris;
    int liberte; // konbyen enteseksyon lib ki vwazin a group la
    int contient_rosette; // si li gen egzagonal yon sel koule
    PionType type; // tip pyon ki fome gwoup la
    DataStructure *elements; // lis eleman nan gwoup la
} Groupe;

int detruire_groupe(Groupe *groupe, int groupe_pris);
Groupe* creer_groupe(Intersection *inter);

#endif //ROSETTE_LOGIC_H
