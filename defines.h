#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED
#include "rosettedata.h"
/* ERREUR codes. */
#define      ROSETTE_OK                     0
#define      ROSETTE_ERREUR_ALLEGRO         1
#define      ROSETTE_ERREUR_GFX             2
#define      ROSETTE_ERREUR_MEMOIRE         3
#define      ROSETTE_ERREUR_MEMOIRE_VIDEO   4
#define      ROSETTE_ERREUR_TRIPLEBUFFER    5
#define      ROSETTE_ERREUR_DONNEE          6
#define      ROSETTE_ERREUR_DONNEE_JEU      7

/* Screen update driver IDs */
#define      ROSETTE_MAJ_DIRECT      0
#define      ROSETTE_DOUBLE_TAMPON   1
#define      ROSETTE_CH_PAGE         2
#define      ROSETTE_TRIPLE_TAMPON   3
#define      ROSETTE_OGL_CH          4


/* Identifiants des etast de jeu/ecrans
*/
#define      ROSETTE_ETAT_MENU_PRINCIPAL 9
#define      ROSETTE_ETAT_NOUVEAU_JEU    1
#define      ROSETTE_ETAT_OPTIONS        2
#define      ROSETTE_ETAT_GFX            3
#define      ROSETTE_ETAT_SON            4
#define      ROSETTE_ETAT_ABOUT          7
#define      ROSETTE_ETAT_AIDE           8
#define      ROSETTE_ETAT_INTRO          0
#define      ROSETTE_ETAT_CONTINUER_JEU 10
#define      ROSETTE_ETAT_SUCCES        11
#define      ROSETTE_ETAT_SORTIE        -1

/* Taille des tampons contenant les chemins vers les differents fichiers du jeu */
#define      ROSETTE_CHEMIN_LN      1024

/* La taille du tableau stockant les etats du jeu */
#define      ROSETTE_MAX_ETATS_JEU    64

/* Skater can use both AllegroGL and plain Allegro fonts. AllegroGL fonts
   require somewhat more code but are much faster that Allegro fonts. */
/* By defualt, use AllegroGL fonts if building in AllegroGL mode. */
#ifdef ROSETTE_USE_ALLEGRO_GL
   #define ROSETTE_USE_ALLEGRO_GL_FONT
#endif

#endif // DEFINES_H_INCLUDED
