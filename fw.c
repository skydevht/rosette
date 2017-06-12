#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include "global.h"
#include "etatjeu.h"
#include "intro.h"
#include "jeu.h"
#include "souris.h"
#include "transition.h"
#include "menus.h"
#include "fw.h"
#include "clavier.h"
#include "aide.h"

static ETATJEU etat[ROSETTE_MAX_ETATS_JEU]; // tablo kap stoke diferan eta je yo
static int etat_courant = 0, dernier_etat; // nou komanse ak zewo ki se entro
static int nombre_etats = 0; // yon fason pou nou pa al two lwen nan tablo a
static int chrono = 0; // Pou stoke kobyen entaval ki pase anvan mizajou
static int ferme = false; // eske ekran an feme
static TRANSITION *transition = NULL; // adres done tranzisyon an kou a

ALLEGRO_EVENT_QUEUE *event_queue; // varyab global ki ap stoke lis evenman

int init_fw()
{
    int erreur = ROSETTE_OK; //Ya, anyen po ko rive
    int c;

    //Essai d'initilisation d'Allegro
    if(!al_init())
        return ROSETTE_ERREUR_ALLEGRO;
    // insisyalize ekstansyon allegro yo
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();


    al_set_app_name("Rosette");
    al_set_org_name("");

    strncpy(data_path, "data", 5);

    al_set_window_title(ecran, "Rosette");

    al_install_audio(); // inisyalizasyon sistem son
    al_init_acodec_addon(); // inisyalizasyon foma fichye mizik
    al_reserve_samples(8); // Defini nonb de son ki ka jwe "a la fois"

    event_queue = al_create_event_queue(); // kreyasyon lis kap stoke evenman

    /* Eseye paremetre mod grafik je a */
    if ((erreur = changer_mode_graphique()) != ROSETTE_OK) {
        fprintf(stderr, "Error: %s\n", erreur_rosette(erreur));
        return erreur;
    }

    if (!al_install_keyboard()) {
        return ROSETTE_ERREUR_ALLEGRO;
    }
    al_install_mouse();


    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    {
      ALLEGRO_TIMER *t = al_create_timer(1.0 / logic_framerate); // kreyasyon entaval
      al_register_event_source(event_queue, al_get_timer_event_source(t)); // anrejistreman li
      al_start_timer(t);// demare l'
   }

   c = ROSETTE_MAX_ETATS_JEU;
   while (c--)
   {
       etat[c].deinit = etat[c].init = NULL;
       etat[c].id = etat[c].maj = NULL;
       etat[c].afficher = NULL;
   } // nou mete tout eleman tablo a null pou evite

    creer_intro(&etat[0]); // kreye eta entwo nan tablo nan pozisyon 0
    creer_nouveau_jeu(&etat[1]);
    creer_continuer_jeu(&etat[2]);
    creer_menu_principal(&etat[3]);
    creer_aide(&etat[4]);

    nombre_etats = 5; // yon fason pou nou konnen konbye eta nou kreye an reyalite

    etat_courant = 0; // nou komanse ak entwo

   return erreur; // L'ap toujou ROSETTE_OK si anyen pa rive
}

static void afficher_fw(){
    if (transition) {
        afficher_transition(transition);
    } else {
        // Nou verifye ke dapre mizajou a, nou pap soti nan jwet la
        if (etat_courant != ROSETTE_ETAT_SORTIE) etat[etat_courant].afficher();
    }
    al_flip_display(); // se la afichaj je a mete an plas
}

void lancer_fw() {
    int fini = false; // Kondisyon pou bouk je a
    int reafficher = 1; // eske nou dwe afiche ?
    int etat_suivant = etat_courant; // apre, se mw :)
    int i; //pou tout ti bouk nou ta rankontre
    bool paused = false;

    etat[etat_courant].init(); // nou inisyalize premye eta jwet la
    // TODO transition entree ici
    chrono = 0; // nonb entaval ki pase

    while (!fini) {
        // jesyon evenman
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES: //mouvman souri
                souris_gerer_evenement(&event);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: // Yo peze yon bouton
                souris_gerer_evenement(&event);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: // Yo lache yon bouton ki te peze
                souris_gerer_evenement(&event);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE: // fenet la femen
                ferme = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                clavier_gerer_evenement(&event);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                clavier_gerer_evenement(&event);
                break;
            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(ecran);
                largeur_ecran = al_get_display_width(ecran);
                hauteur_ecran = al_get_display_height(ecran);
                if (pleinecran == 0) {
                    largeur_fenetre = largeur_ecran;
                    hauteur_fenetre = hauteur_ecran;
                }
                break;
            case ALLEGRO_EVENT_TIMER: // yon enteval pase
                if (!paused)
                    chrono++;
                break;
            // TODO ajouter le reste des evenements
        }

        if (!al_is_event_queue_empty(event_queue)) continue;
        while (chrono > 0) { // egzekite  l' selman si yon entaval pase, e nob de fwa enteval la pase
            --chrono; // nou trete yon entaval
            if (transition) { // yon tranzisyon an kou
                if (maj_transition(transition) == 0) { // fe mizajou e verifye si nou pa temine
                    detruire_transition(transition); // detwi tranzisyon an
                    transition = NULL;
                    if (etat[dernier_etat].deinit) { // verifye ke gen yon fonksyon pou deinisyalize
                        etat[dernier_etat].deinit(); // denisyalize eta nou te ye anvan tranzisyon an
                    }
                    if (etat_courant == ROSETTE_ETAT_SORTIE) { // si je a temine
                        fini = true; // pou nou soti nan bouk je a
                        break; // soti nan mizajou a
                    }
                }
            }
            else {
                etat_suivant = etat[etat_courant].maj(); // fe mizajou eta nou ye a, e stoke eta nou pral apre a
                if (etat_suivant == ROSETTE_ETAT_SORTIE) {
                    transition = creer_transition(&etat[etat_courant], NULL, 0.3f);
                    dernier_etat = etat_courant;
                    etat_courant = etat_suivant;
                    break;
                }
                else if (etat_suivant != etat[etat_courant].id()) {
                    // ya, nou soti nan eta nou te ye a, :)
                    dernier_etat = etat_courant;
                    // ki nouvo eta nou ye a?
                    for (i = 0; i < nombre_etats; i++) {
                        if (etat[i].id() == etat_suivant) {
                            // Nou konn eta nou ye kounya, :)
                            etat[i].init(); // inisyalize eta a
                            transition = creer_transition(&etat[etat_courant], &etat[i], 1); // kreye yon transisyon ant ansyen eta nou ak nouvo a
                            etat_courant = i; // mete nouvo eta nou kom bon eta a
                            break;
                        }
                    }
                }
            }
            reafficher = 1; // Fok nou reyafiche, nou sot fe yon mizajou

            clavier_tick(); // Nou jere evenman klavye, reyinisyalize gesyone klavye
            souris_tick(); // Nou jere evenman souri, reyinisyalize gesyone evenman souri
        }
        // TODO gerer mise en fond
        if (reafficher == 1 ) { // Nou pa dwe afiche konsa konsa
            afficher_fw();
            reafficher = 0; // Nou afiche, pa deranje nou si pa gen mizajou anko
        }

        fini = fini || ferme; // sin temine oswa ekran femen, soti
    }

}

void arreter_fw(){
    al_destroy_event_queue(event_queue); // rekipere espas memwa a
}
