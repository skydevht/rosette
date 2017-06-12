#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "defines.h"

/* Some configuration settings. All of these variables are recorded
   in the configuration file. */


extern int pleinecran; // tout ekran an?
extern int bit_depth; // vreman pa nesese, men se jis ke pou nou ka presize konbye koule nou bezwen le nou pran tout ekran an
extern int largeur_ecran; // rezolisyon orizontal
extern int hauteur_ecran; // rezolisyon vetikal
extern int largeur_fenetre;         /* remember last window width */
extern int hauteur_fenetre;        /* remember last window height */
extern int logic_framerate;      /* target logic framerate */

/* Absolute path of the config file. */
extern char config_path[ROSETTE_CHEMIN_LN];

/* Absolute path of the datafile. */
extern char data_path[ROSETTE_CHEMIN_LN];

/* The main menu font (monochrome). */
#define demo_font ((ALLEGRO_FONT *)demo_data[DEMO_FONT].dat)

/* The big title font (coloured). */
#define demo_font_logo ((ALLEGRO_FONT *)demo_data[DEMO_FONT_LOGO].dat)

/* Font made of default allegro font (monochrome). */
#define plain_font demo_font

extern ALLEGRO_DISPLAY *ecran;


/*
   Converts an error code to an error description.

   Parameters:
      int id - error code (see defines.h)

   Returns:
      String containing the description of the error code.
*/
extern const char *erreur_rosette(int id);

extern int changer_mode_graphique();

extern void unload_data(void);

typedef struct DATA_ENTRY {
   int id;
   char const *type;
   char *path;
   char *subfolder;
   char *name;
   char *ext;
   int size;
   void *dat;
} DATA_ENTRY;

extern DATA_ENTRY *donnee_rosette;

void unload_data_entries(DATA_ENTRY *data);

#endif // GLOBAL_H_INCLUDED
