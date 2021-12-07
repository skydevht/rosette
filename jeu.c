#include <allegro5/allegro.h>
#include <math.h>
#include "defines.h"
#include "jeu.h"
#include "board.h"
#include "clavier.h"
#include "UI/button.h"
#include "menus.h"

View *screen_view;
ALLEGRO_BITMAP *fin_bg;
static Player *joueurs[2];
int joueur_actif;
int joueur_gagnant, score_gagnant, score_perdant;
Hud huds[2];
int etat_suivant;
static int paused = 0;
static int fin = 0;


Button *resume_btn, *exit_btn, *new_btn;

void resume_click_handler(){
    paused = (paused) ? 0 : 1;
}
void new_click_handler(){
    etat_suivant = ROSETTE_ETAT_NOUVEAU_JEU;
}

void exit_click_handler(){
    if (!fin) {
        paused = 0;
    } else {
    }
    etat_suivant = ROSETTE_ETAT_MENU_PRINCIPAL;
}

void augmenter_score(int couleur_pion_pris, int score) {
    int id = (couleur_pion_pris == P_BLACK) ? J2 : J1;
    joueurs[id]->score += score;

}

void changer_joueur(int ancien_joueur) {
    int new_id = joueur_actif = (ancien_joueur == J1) ? J2 : J1;
    joueurs[new_id]->active = 1;
    joueurs[ancien_joueur]->active = 0;
}

Player * trouver_joueur_actif(){
    return joueurs[joueur_actif];
}

static int _idnouveau = ROSETTE_ETAT_NOUVEAU_JEU;
static int idnouveau()
{
    return _idnouveau;
}
static int _idcontinuer = ROSETTE_ETAT_CONTINUER_JEU;
static int idcontinuer()
{
    return _idcontinuer;
}

static int IDCourrant;


static void InitNouveau()
{
    // kreye jwe yo
    for (int i = 0; i < 2; i++){
        joueurs[i] = malloc(sizeof(Player));
        joueurs[i]->id = i;
        joueurs[i]->active = (i == J1) ? 1: 0; // pyon nwa anvan
        joueurs[i]->pions_restants = 150;
        joueurs[i]->score = 0;
        huds[i].player = joueurs[i];
        init_hud(&huds[i], i);
    }
    joueur_actif = J1;
    init_board();
    etat_suivant = IDCourrant = idnouveau();
    resume_btn = create_button(largeur_ecran /2.0, 300, donnee_rosette[ROSETTE_GAME_RESUME_BTN].dat, donnee_rosette[ROSETTE_GAME_RESUME_BTN_HOVER].dat);
    resume_btn->click_handler = resume_click_handler;
    new_btn = create_button(largeur_ecran /2.0, 300, donnee_rosette[ROSETTE_GAME_NEW_BTN].dat, donnee_rosette[ROSETTE_GAME_NEW_BTN_HOVER].dat);
    new_btn->click_handler = new_click_handler;
    exit_btn = create_button(largeur_ecran /2.0, 450, donnee_rosette[ROSETTE_GAME_EXIT_BTN].dat, donnee_rosette[ROSETTE_GAME_EXIT_BTN_HOVER].dat);
    exit_btn->click_handler = exit_click_handler;
    activer_continuer_jeu();
    fin_bg = al_create_bitmap(largeur_ecran, hauteur_ecran);
}

static void InitContinuer()
{
    etat_suivant = IDCourrant = idcontinuer();
}

static int MajJeu()
{
    // TODO execute only if mouse clicked in the surround box
    if (!fin) {
        if (!paused) {
            maj_board();
            maj_hud(&huds[0]);
            maj_hud(&huds[1]);
        } else {
            maj_button(resume_btn);
            maj_button(exit_btn);
        }
        if (clavier_touche_relachee(ALLEGRO_KEY_ESCAPE)) paused = (paused)? 0 : 1;
    } else {
        maj_button(new_btn);
        maj_button(exit_btn);
    }
    return etat_suivant;
}

static void AfficherJeu()
{
    al_clear_to_color(al_map_rgb(255, 255, 255));
    if (!fin) {
        al_draw_scaled_bitmap(donnee_rosette[ROSETTE_MAIN_BG].dat, 0, 0, 1200, 675, 0, 0, largeur_ecran, hauteur_ecran, 0);
        afficher_board();
        afficher_hud(&huds[0]);
        afficher_hud(&huds[1]);
        if (paused) {
            al_draw_filled_rectangle(0, 0, largeur_ecran, hauteur_ecran, al_map_rgba_f(0, 0, 0, 0.7));
            al_draw_text(donnee_rosette[ROSETTE_HUD_SCORE_FONT].dat, al_map_rgb(0, 150, 136), largeur_ecran/2.0, 100, ALLEGRO_ALIGN_CENTER, "PAUSE");
            draw_button(resume_btn);
            draw_button(exit_btn);
        }
    } else {
        char message[50];
        al_draw_bitmap(fin_bg, 0, 0, 0);
        al_draw_filled_rectangle(0, 0, largeur_ecran, hauteur_ecran, al_map_rgba_f(0, 0, 0, 0.7));
        al_draw_text(donnee_rosette[ROSETTE_HUD_SCORE_FONT].dat, al_map_rgb(0, 150, 136), largeur_ecran/2.0, 100, ALLEGRO_ALIGN_CENTER, "TERMINÉ");
        if (joueur_gagnant == 2) {
            al_draw_text(donnee_rosette[ROSETTE_HUD_LEFT_PAWN_FONT].dat, al_map_rgb(0, 150, 136), largeur_ecran/2.0, 200, ALLEGRO_ALIGN_CENTER, "MATCH NULL!");
        } else {
            int other = (joueur_gagnant == 0) ? 1 : 0;
            snprintf(message, 50, "Gagnant : Joueur %d | %d - %d", joueur_gagnant + 1, score_gagnant, score_perdant);

            al_draw_text(donnee_rosette[ROSETTE_HUD_LEFT_PAWN_FONT].dat, al_map_rgb(0, 150, 136), largeur_ecran/2.0, 200, ALLEGRO_ALIGN_CENTER, message);
        }

        draw_button(new_btn);
        draw_button(exit_btn);
    }
}

static void DeinitJeu()
{
    if (fin){
        destroy_button(new_btn);
        destroy_button(exit_btn);
        fin = 0;
    }
}

void creer_nouveau_jeu(ETATJEU *etat)
{
    etat->id = idnouveau;
    etat->init = InitNouveau;
    etat->maj = MajJeu;
    etat->afficher = AfficherJeu;
    etat->deinit = DeinitJeu;
}

void creer_continuer_jeu(ETATJEU *etat)
{
    etat->id = idcontinuer;
    etat->init = InitContinuer;
    etat->maj = MajJeu;
    etat->afficher = AfficherJeu;
    etat->deinit = DeinitJeu;
}

void terminer_jeu(){
    ALLEGRO_BITMAP *last_bmp;
    last_bmp = al_get_target_bitmap();
    al_set_target_bitmap(fin_bg);
    AfficherJeu();
    al_set_target_bitmap(last_bmp);
    // Kiyes ki genyen?
    if (joueurs[0]->score == joueurs[1]->score)
        joueur_gagnant = 2;
    else {
        joueur_gagnant = (joueurs[0]->score > joueurs[1]->score) ? 0 : 1;
        int other = (joueur_gagnant == 0) ? 1 : 0;
        score_gagnant = joueurs[joueur_gagnant]->score;
        score_perdant = joueurs[other]->score;
    }
    fin = 1;
    detruire_jeu();
}

void detruire_jeu()
{
    for (int i = 0; i < 2; i++){
        free(joueurs[i]);
        deinit_hud(&huds[i]);
    }
    deinit_board();
    destroy_button(resume_btn);
    activer_nouveau_jeu();
}