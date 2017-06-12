//
// Created by Hash on 4/15/2016.
//

#include "logic.h"
#include "board.h"
#include "jeu.h"

// TODO : Regle kesyon egzagon ki pa egziste nan tablo a


void chaine(Intersection *inter, Groupe *groupe);

int part_of_rosette(const Intersection *next_inter, int deja_pris);

Groupe *creer_groupe(Intersection *inter) {
    // verifye ke premye eleman an pa vid
    if (inter->libre || !inter->used || inter->visited) return NULL;

    // inisyalize varyab wap bezwen
    Groupe *groupe = malloc(sizeof(Groupe));
    groupe->type = inter->pion->type;
    char *type = (groupe->type == P_BLACK) ? "Pion noir" : "Pion blanc";
    printf("\tType : %s\n", type);
    groupe->liberte = 0;
    groupe->pris = 1;
    groupe->contient_rosette = 0;
    groupe->elements = init_data_structure(STACK);

    chaine(inter, groupe);
    printf("\tGroupe pris : %s\n", ((groupe->pris)? "Oui": "Non"));
    printf("\n");
    return groupe;
}







void chaine(Intersection *inter, Groupe *groupe) {
    DataStructure *check_groupe = init_data_structure(STACK);
    // ajoute premye eleman nan lis la, apre make l'
    intersection_stack_push(check_groupe, inter);
    inter->visited = 1;

    // toutotan lis la pa vid
    while (check_groupe->count > 0) {
        // retire yon enteseksyon nan lis la
        Intersection *next_inter = intersection_stack_pop(check_groupe);

        // ajoute l nan gwoup la pou efase mak la e detwi li si yo pran gwoup la
        intersection_stack_push(groupe->elements, next_inter);

        // gade si inteseksyon an fe pati de yon rozet
        groupe->pris = part_of_rosette(next_inter, groupe->pris);

        // trete enteseksyon ki adjasan yo
        for (int i = 0; i < 3; i++) {
            Intersection *next_inter_voisin = next_inter->voisin[i];
            // si li pa vizite ou si li fe pati de damye a
            if (next_inter_voisin->visited == 0 && next_inter_voisin->used == 1) {
                // si li gen pyon
                if (next_inter_voisin->libre == 0) {
                    // verifye kel menm koule ak lot nan gwoup la
                    if (next_inter_voisin->pion->type == groupe->type) {
                        //makel e ajoutel nan lis la pou ka trete l
                        next_inter_voisin->visited = 1;
                        intersection_stack_push(check_groupe, next_inter_voisin);
                    }
                }
                    // sinon
                else {
                    // ogmante libet gwoup la
                    groupe->liberte++;
                    groupe->pris = 0;
                    // makel pou pa rekontel
                    next_inter_voisin->visited = 1;
                    // ajoutel nan gwoup la pou ka efase mak la;
                    intersection_stack_push(groupe->elements, next_inter_voisin);
                }
            }
        }
    }
    free(check_groupe);
}










int part_of_rosette(const Intersection *next_inter, int deja_pris) {
    Hex hexes[3]; // stoke hegzagonal li touche
    vertex_touches(&next_inter->hex_position, hexes);
    for (int j = 0; j < 3; j++) {
        Hexagonal *hexagonal = trouver_hexagone(hexes[j].q, hexes[j].r, hexes[j].s);
        deja_pris =  (next_inter->pion->type == P_BLACK) ? (hexagonal->black_count == 6) ? 0 : deja_pris : (hexagonal->white_count == 6) ? 0 : deja_pris;
    }
    return deja_pris;
}

int detruire_groupe(Groupe *groupe, int groupe_pris) {
    if (!groupe) return 0;
    int score = 0;
    //toutotan gwoup la gen inteseksyon
    while (groupe->elements->count > 0) {
        // retire youn
        Intersection *next_inter = intersection_stack_pop(groupe->elements);

        // si enteseksyon an gen pyon e yo pran gwoup la
        if (next_inter->libre == 0 && groupe->pris) {
            // retire pyon an e rekipere memwa a
            Hex hexes[3]; // stoke hegzagonal li touche
            vertex_touches(&next_inter->hex_position, hexes);
            for (int i = 0; i < 3; i++) {
                Hexagonal *hex = trouver_hexagone(hexes[i].q, hexes[i].r, hexes[i].s);
                (next_inter->pion->type == P_BLACK) ? hex->black_count-- : hex->white_count--;
            }
            free(next_inter->pion);
            next_inter->pion = NULL;
            next_inter->libre = 1;
            score++;
        }
        // nap toujou retire mak la
        next_inter->visited = 0;
    }
    augmenter_score(groupe->type, score);

    //rekipere memwa a
    free(groupe->elements);
    free(groupe);
    return 1;
}