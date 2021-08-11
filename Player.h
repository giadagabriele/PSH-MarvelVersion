#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//      La classe Player carica le immagini del player sulla mappa


//		Il metodo draw disegna il player, in base alla direzione

class Player : public Creature
{
    private:
        ALLEGRO_BITMAP *playerL;
        ALLEGRO_BITMAP *playerR;
        int life;
    public:
        Player(int x,int y) : Creature(2, x, y) 
        {
            direction = 1;
            playerL=al_load_bitmap("Immagini/playerLeft.png");
            playerR=al_load_bitmap("Immagini/playerRight.png");
            life = 3;
        }
        Player(int x,int y,int l) : Creature(x, y) 
        {
            direction=1;
            playerL=al_load_bitmap("Immagini/playerLeft.png");
            playerR=al_load_bitmap("Immagini/playerRight.png");
            life = l;
        }
        void draw(int direction, int i, int j)
        {
            if(direction==1)
                al_draw_bitmap(playerL,j,i,0);
            else
                al_draw_bitmap(playerR,j,i,0);
        }
        int getLife() const { return life; }
        void setLife(int l) { life=l; }

};

#endif
