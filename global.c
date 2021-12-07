#include <allegro5/allegro.h>
#include <stdio.h>
#include <ctype.h>
// #include <mem.h>

#include "global.h"
#include "fw.h"
#include "rosettedata.h"

ALLEGRO_DISPLAY *ecran;
int pleinecran = 0;
int logic_framerate = 100;
int largeur_ecran = 1200;
int hauteur_ecran = 675;
int echantillons_ecran = 1;
int largeur_fenetre = 1200;
int hauteur_fenetre = 675;

DATA_ENTRY *donnee_rosette;
char data_path[ROSETTE_CHEMIN_LN];

int load_data(void);



/*
 *  Jis pou jwenn ka afiche ere a bay itilizate a
 *
 * */
const char *erreur_rosette(int id) {
    switch (id) {
        case ROSETTE_ERREUR_ALLEGRO:
            return "Erreur Allegro";
        case ROSETTE_ERREUR_GFX:
            return "Impossible de trouver un pilote graphique";
        case ROSETTE_ERREUR_MEMOIRE:
            return "Memoire pleine";
        case ROSETTE_ERREUR_MEMOIRE_VIDEO:
            return "Pas assez de memoire video";
        case ROSETTE_ERREUR_TRIPLEBUFFER:
            return "tampon triple non supporte";
        case ROSETTE_ERREUR_DONNEE:
            return "impossible de charger les donnees du menu";
        case ROSETTE_ERREUR_DONNEE_JEU:
            return "Erreur jeu";
        case ROSETTE_OK:
            return "OK";
        default:
            return "inconnu";
    };
}

/*
 * Responsab pou krerasyon fenet la swivan plizye paramet e detwi ansyen fenet la si l' prezan
 *
 * */

int changer_mode_graphique(void)
{
    int ret = ROSETTE_OK;
    int flags = 0;

    /* Select appropriate (fullecran or windowed) gfx mode driver. */
    if (pleinecran == 0) {
        flags |= ALLEGRO_WINDOWED; //ALLEGRO_RESIZABLE;
        largeur_ecran = largeur_fenetre;
        hauteur_ecran = hauteur_fenetre;
    } else if (pleinecran == 1) {
        flags |= ALLEGRO_FULLSCREEN_WINDOW;
    } else {
        flags |= ALLEGRO_FULLSCREEN;
    }

    if (ecran) {
        al_destroy_display(ecran);
    }

    al_set_new_display_flags(flags);

    // May be a good idea, but need to add a border to textures for it.
    // al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    if (echantillons_ecran > 1) {
        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
        al_set_new_display_option(ALLEGRO_SAMPLES, echantillons_ecran, ALLEGRO_SUGGEST);
    }
    else {
        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 0, ALLEGRO_SUGGEST);
        al_set_new_display_option(ALLEGRO_SAMPLES, 0, ALLEGRO_SUGGEST);
    }

    al_set_new_display_option(ALLEGRO_SUPPORTED_ORIENTATIONS,
                              ALLEGRO_DISPLAY_ORIENTATION_LANDSCAPE, ALLEGRO_SUGGEST);

    /* Attempt to set the selected colour depth and gfx mode. */
    ecran = al_create_display(largeur_ecran, hauteur_ecran);
    if (!ecran) {
        return ROSETTE_ERREUR_ALLEGRO;
    }
    al_set_window_constraints(ecran, 320, 320, 0, 0);

    largeur_ecran = al_get_display_width(ecran);
    hauteur_ecran = al_get_display_height(ecran);
    //ecran_orientation = ALLEGRO_DISPLAY_ORIENTATION_90_DEGREES;

    al_register_event_source(event_queue, al_get_display_event_source(ecran));

    /* blank display now, before doing any more complicated stuff */
    al_clear_to_color(al_map_rgb(0, 0, 0));

    /* Attempt to load game data. */
    ret = load_data();

    /* If loading was successful, initialize the background scroller module. */
    if (ret == ROSETTE_OK) {
        //init_background();
    }

    return ret;
}

static bool load(DATA_ENTRY *d, int id, char const *type, char const *path,
                 char const *subfolder, char const *name, char const *ext, int size)
{
    static char spath[1024];
    sprintf(spath, "%s/%s/%s.%s", path, subfolder, name, ext);
    printf("Loading %s...\n", spath);
    if (!strcmp(type, "font")) d[id].dat = al_load_font(spath, size, 0);
    if (!strcmp(type, "bitmap")) d[id].dat = al_load_bitmap(spath);
    if (!strcmp(type, "sample")) d[id].dat = al_load_sample(spath);
    if (!strcmp(type, "music")) d[id].dat = al_load_audio_stream(spath, 2, 4096);
    if (d[id].dat == NULL) {
        printf("Failed loading %s.\n", name);
    }
    d[id].type = type;
    d[id].path = strdup(path);
    d[id].subfolder = strdup(subfolder);
    d[id].name = strdup(name);
    d[id].ext = strdup(ext);
    d[id].size = size;
    return d[id].dat != NULL;
}



static DATA_ENTRY *load_data_entries(char const *path)
{
    DATA_ENTRY *d = calloc(ROSETTE_DATA_COUNT + 1, sizeof *d);

    load(d, ROSETTE_INTRO_BG, "bitmap", path, "img", "r_bg", "jpg", 0);
    load(d, ROSETTE_MAIN_BG, "bitmap", path, "img", "bg", "jpg", 0);
    load(d, ROSETTE_MAIN_MENU_TITLE, "bitmap", path, "sprite", "main_menu_title", "png", 0);
    load(d, ROSETTE_MAIN_MENU_PLAY_BTN, "bitmap", path, "sprite", "main_menu_play_btn", "png", 0);
    load(d, ROSETTE_MAIN_MENU_PLAY_BTN_HOVER, "bitmap", path, "sprite", "main_menu_play_btn_hover", "png", 0);
    load(d, ROSETTE_MAIN_MENU_RESUME_BTN, "bitmap", path, "sprite", "main_menu_resume_btn", "png", 0);
    load(d, ROSETTE_MAIN_MENU_RESUME_BTN_HOVER, "bitmap", path, "sprite", "main_menu_resume_btn_hover", "png", 0);
    load(d, ROSETTE_MAIN_MENU_HELP_BTN, "bitmap", path, "sprite", "main_menu_help_btn", "png", 0);
    load(d, ROSETTE_MAIN_MENU_HELP_BTN_HOVER, "bitmap", path, "sprite", "main_menu_help_btn_hover", "png", 0);
    load(d, ROSETTE_MAIN_MENU_QUIT_BTN, "bitmap", path, "sprite", "main_menu_quit_btn", "png", 0);
    load(d, ROSETTE_MAIN_MENU_QUIT_BTN_HOVER, "bitmap", path, "sprite", "main_menu_quit_btn_hover", "png", 0);
    load(d, ROSETTE_GAME_EXIT_BTN, "bitmap", path, "sprite", "exit_game_btn", "png", 0);
    load(d, ROSETTE_GAME_EXIT_BTN_HOVER, "bitmap", path, "sprite", "exit_game_btn_hover", "png", 0);
    load(d, ROSETTE_GAME_RESUME_BTN, "bitmap", path, "sprite", "game_resume_btn", "png", 0);
    load(d, ROSETTE_GAME_RESUME_BTN_HOVER, "bitmap", path, "sprite", "game_resume_btn_hover", "png", 0);
    load(d, ROSETTE_GAME_NEW_BTN, "bitmap", path, "sprite", "game_new", "png", 0);
    load(d, ROSETTE_GAME_NEW_BTN_HOVER, "bitmap", path, "sprite", "game_new_hover", "png", 0);
    load(d, ROSETTE_GAME_PASS_BTN, "bitmap", path, "sprite", "game_pass_btn", "png", 0);
    load(d, ROSETTE_GAME_PASS_BTN_HOVER, "bitmap", path, "sprite", "game_pass_btn_hover", "png", 0);
    load(d, ROSETTE_GAME_QUIT_BTN, "bitmap", path, "sprite", "game_quit_btn", "png", 0);
    load(d, ROSETTE_GAME_QUIT_BTN_HOVER, "bitmap", path, "sprite", "game_quit_btn_hover", "png", 0);
    load(d, ROSETTE_HUD_TITLE_FONT, "font", path, "fonts", "akashi", "ttf", 72);
    load(d, ROSETTE_HUD_SCORE_FONT, "font", path, "fonts", "akashi", "ttf", 100);
    load(d, ROSETTE_HUD_LEFT_PAWN_FONT, "font", path, "fonts", "akashi", "ttf", 24);

    return d;
}

void unload_data_entries(DATA_ENTRY *data)
{
    while (data && data->dat) {
        if (!strcmp(data->type, "bitmap")) al_destroy_bitmap(data->dat);
        if (!strcmp(data->type, "font")) al_destroy_font(data->dat);
        if (!strcmp(data->type, "sample")) al_destroy_sample(data->dat);
        if (!strcmp(data->type, "music")) al_destroy_audio_stream(data->dat);
        data++;
    }
}

int load_data(void)
{
    if (donnee_rosette)
        return ROSETTE_OK;

    /* Load the data for the game menus. */
    donnee_rosette = load_data_entries(data_path);
    if (donnee_rosette == 0) {
        return ROSETTE_ERREUR_DONNEE;
    }

    /* Load other game resources. */

    return ROSETTE_OK;
}


void unload_data(void)
{
    if (donnee_rosette != 0) {
        unload_data_entries(donnee_rosette);
        donnee_rosette = 0;
    }
}
