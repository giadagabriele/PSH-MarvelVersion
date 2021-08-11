#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GameManager.h"
#include <sstream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h> 

//  Il costruttore inizializza allegro, pone l'array di chiavi per la pressione dei tasti a false, 
//  il redraw e il doExit a false e definisce la dimensione del display di gioco

//  Il metodo Game esegue il loop del gioco. al suo interno viene richiamata la funzione moveEnemy 
//  per il movimento random di ogni enemy. se la variabile  drop è true, ovvero ho preso il barile, 
//  posso provare a lanciarlo. Aggiorno la direzione e la posizione del player in base alla pressione 
//  su un tasto della tastiera. 

enum Keys { KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_A, KEY_S, KEY_ENTER};

class Graphics
{
  private:
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_DISPLAY_MODE disp_data;
    ALLEGRO_TRANSFORM resize;
    ALLEGRO_EVENT_QUEUE *event_queue=NULL;
    ALLEGRO_TIMER *enemyTimer=NULL;
    ALLEGRO_TIMER *timer=NULL;
    ALLEGRO_BITMAP *start=NULL;
    ALLEGRO_BITMAP *wall=NULL;
    ALLEGRO_BITMAP *barrel=NULL;
    ALLEGRO_BITMAP *barrelND=NULL;
    ALLEGRO_BITMAP *lose=NULL;
    ALLEGRO_BITMAP *win=NULL;
    ALLEGRO_FONT *text=NULL;
    
    int FPS;
    float speed;   
    GameManager gameManager;
    bool key[7];
    bool redraw;
    bool doExit;

    public:
        Graphics();
        void Game();
        void Load();
        bool Start();
        void Draw();
        void Check();
        ~Graphics();
};

#endif